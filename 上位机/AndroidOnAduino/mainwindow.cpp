#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QDebug>
#include <QMessageBox>
#include "SwitchControl.h"
#include <QColor>
#include <QTransform>
#include <QThread>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),Run(false),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //加载需要用到的图标
    this->openImg.load(":/new/prefix1/Resource/open.png");
    this->closeImg.load(":/new/prefix1/Resource/close.png");
    this->capacityImg.load(":/new/prefix1/Resource/capacity.png");
    //创建socket对象
    m_socket=new QTcpSocket;

    //设置当前窗帘初始状态为关
    ui->motorState->setPixmap(closeImg);

    //创建智能模式开关
    switch_intelligence=newSwitchControl(false,QColor(0,160,230));
    switch_intelligence->resize(200,30);
    text_intelligence=new QLabel(this);

    //创建手动模式开关
    switch_handMovement=newSwitchControl(false,QColor(0,160,230));
    switch_handMovement->resize(200,30);
    text_handMovement=new QLabel(this);

    m_timerId=startTimer(10);

    //使能主界面控制开关不可用
    this->setSwtichState(false);


    //设置返回按钮位置
    ui->back->move(0,300);

//    this->AduinoLabel=new QLabel(this);
//    this->AduinoLabel->setText(tr("超声波距离显示："));
//    //设置Label皮肤，和显示
//    QPalette pal = palette();
//    //pal.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));//全透明
//    pal.setColor(QPalette::Background, QColor(0xc5,0,0,100));//半透明
//    this->AduinoLabel->setGeometry(this->window()->width()/2/2,this->window()->height()/2/2,140,220);
//    this->AduinoLabel->setPalette(pal);
//    this->AduinoLabel->show();

    //创建连接对话框
    dlg=new Dialog();
    dlg->resize(this->window()->width(), this->window()->height());
    dlg->setStyleSheet("background-color:#33ff33;");

    //关联返回按钮，信号
    connect(ui->back,SIGNAL(clicked(bool)),this,SLOT(showConnectDialog()));
    //关联自动控制按钮信号
    connect(switch_intelligence,SIGNAL(toggled(bool)),this,SLOT(btn_intelligence(bool)));
    //关联手动控制按钮信号
    connect(switch_handMovement,SIGNAL(toggled(bool)),this,SLOT(btn_handMovement(bool)));
    //关联自定义信号
    connect(dlg,SIGNAL(sendConnectInfo(QStringList)),this,SLOT(reshow(QStringList)));

    if(dlg->exec()==Dialog::Accepted){
        //用户正确的点击了连接按钮
        //尝试建立通信
        this->m_socket->connectToHost(host_name,port,QTcpSocket::ReadWrite);
        //Run=false;
        //建立信号槽机制，当收到服务端发来的信息时，就
        connect(m_socket,SIGNAL(connected()),this,SLOT(connected()));
        this->m_runTimerId=startTimer(100);//启动，检查网络是否连接成功定时器
    }else{
        exit(0);
    }
}


void MainWindow::connected()
{
    //设置当前窗口为可用
    Run=true;
    //关闭检查网络定时器
    killTimer(m_runTimerId);
    qDebug()<<Run;
    QMessageBox::about(this,"提示","连接成功");
    this->setSwtichState(true);
    //初始化为智能模式
    switch_intelligence->setToggle(true);
    btn_handMovement(true);
    //设置手动模式不可被选中
    switch_handMovement->setEnabled(false);
    ui->pattern->setText("当前模式为：智能模式");
    //设置状态图标
    ui->motorState->setPixmap(this->capacityImg);
    connect(this->m_socket,SIGNAL(readyRead()),this,SLOT(readyread()));

    qDebug()<<switch_intelligence->rect();
}


void MainWindow::timerEvent(QTimerEvent *event){
    if(event->timerId()==m_timerId)
    {
        int intelligenceWidth=this->window()->width()/2;
        int intelligenceHeight=this->window()->height()/2;
        switch_intelligence->move(intelligenceWidth-intelligenceWidth/1.5,intelligenceHeight+intelligenceHeight/2/2);

        text_intelligence->resize(156,50);
        text_intelligence->setText("智能控制：关/开");
        text_intelligence->move(intelligenceWidth-intelligenceWidth/1.5,intelligenceHeight+intelligenceHeight/2/1.2);

        int handMovementWidth=this->window()->width()/2;
        int handMovementHeight=this->window()->height()/2;
        switch_handMovement->move(handMovementWidth+handMovementWidth/2.5,handMovementHeight+handMovementHeight/2/2);

        text_handMovement->resize(156,50);
        text_handMovement->setText("手动控制：关/开");
        text_handMovement->move(handMovementWidth+handMovementWidth/2.5,handMovementHeight+handMovementHeight/2/1.2);
    }
    if(event->timerId()==m_runTimerId){
        qDebug()<<Run;
        if(!Run){
            QMessageBox::about(this,"提示","连接失败，请重新连接");
            showConnectDialog();
        }
    }
}

void MainWindow::showConnectDialog(){
    //取消已有的连接
    m_socket->abort();
    m_socket->close();
    dlg->exec();
    Run=false;
    //尝试建立通信
    this->m_socket->connectToHost(host_name,port,QTcpSocket::ReadWrite);
    this->m_runTimerId=startTimer(100);//启动，检查网络是否连接成功定时器
}

SwitchControl* MainWindow::newSwitchControl(bool toggle,QColor background)
{
    SwitchControl *checkBox=new SwitchControl(this);
    checkBox->setToggle(toggle);
    checkBox->setCheckedColor(background);
    checkBox->setStyleSheet("SwitchControl{border-radius:5px;border-width:0px;}");
    return checkBox;
}

void MainWindow::btn_intelligence(bool flag){
    if(flag){
        //关闭手动模式并且，使能手动开关
        setHandMovementEnbled(false);
        //打开智能模式
        m_socket->write("openNoopsyche");
        ui->pattern->setText("当前模式为：智能");
        ui->motorState->setPixmap(capacityImg);
    }else{
        //开启手动模式
        setHandMovementEnbled(true);
        //关闭智能模式
        m_socket->write("closeNoopsyche");
        ui->pattern->setText("当前模式为：手动");
        ui->motorState->setPixmap(closeImg);
    }
}
void MainWindow::btn_handMovement(bool flag){
    if(flag){
        m_socket->write("open");
        ui->motorState->setPixmap(openImg);
        ui->motorTextState->setText("窗帘状态为：开");
    }else{
        m_socket->write("close");
        ui->motorState->setPixmap(closeImg);
        ui->motorTextState->setText("窗帘状态为：关");
    }
    m_socket->flush();
}


void MainWindow::setSwtichState(bool state){
    switch_handMovement->setEnabled(state);
    switch_intelligence->setEnabled(state);
}

void MainWindow::setHandMovementEnbled(bool state){
    //如果智能模式被开启，就强制关闭手动模式，并且使能手动开关，不可被点击
    if(this->switch_handMovement->isToggled())
    {
        switch_handMovement->setToggle(state);
        btn_handMovement(false);
        switch_handMovement->setEnabled(state);

    }else{
        //设置手动模式不可被选中
        switch_handMovement->setEnabled(state);
    }

}



void MainWindow::reshow(QStringList y){
    host_name=y[0];
    port=atoi(y[1].toStdString().c_str());
}

void MainWindow::readyread()
{
    QString buffer;
    buffer=m_socket->readAll();
    if(buffer.length()<=0){
        return;
    }
    this->AduinoLabel->setText(buffer);
    qDebug()<<buffer;
}

MainWindow::~MainWindow()
{
    delete ui;
}
