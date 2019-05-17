#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QTcpSocket>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    host_name=ui->host_name->text();
    port=ui->port->text();
    connect(ui->connect,SIGNAL(clicked(bool)),this,SLOT(connectServers()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::connectServers(){
    QStringList buf;
    buf.push_back(ui->host_name->text());
    buf.push_back(ui->port->text());
    emit sendConnectInfo(buf);
    this->accept();
}

