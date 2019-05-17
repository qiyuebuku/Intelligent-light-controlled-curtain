#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString host_name;
    QString port;

private:
    Ui::Dialog *ui;
public slots:
    void connectServers();
signals:
    void sendConnectInfo(QStringList);//创建发送数据信号
};

#endif // DIALOG_H
