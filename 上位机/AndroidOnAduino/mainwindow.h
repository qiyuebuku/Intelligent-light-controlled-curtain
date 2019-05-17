#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include <QTcpSocket>
#include "SwitchControl.h"
#include <QLabel>
#include <QPixmap>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SwitchControl *newSwitchControl(bool toggle,QColor background);
    virtual void timerEvent(QTimerEvent *event);
public slots:
    void reshow(QStringList);
    void connected();
    void readyread();
    void setSwtichState(bool state);
    void showConnectDialog();
    void btn_intelligence(bool flag);
    void btn_handMovement(bool flag);
    void setHandMovementEnbled(bool state);

private:
    Ui::MainWindow *ui;
    Dialog *dlg;
    QString host_name;
    int port;
    QTcpSocket *m_socket;
    SwitchControl *switch_intelligence,*switch_handMovement;
    QLabel *text_intelligence,*text_handMovement;
    QPixmap closeImg,openImg,capacityImg;
    QLabel *AduinoLabel;
    bool Run;
    int m_timerId;
    int m_runTimerId;
signals:
    void sendConnectInfo(QStringList);
};

#endif // MAINWINDOW_H
