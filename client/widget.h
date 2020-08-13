#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPoint>
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_connected();
    void on_disconnected();
    void outError(QAbstractSocket::SocketError);
    void on_ReadyRead();
    void on_pathBut_clicked();

    void on_connectBut_clicked();

    void on_sendBut_clicked();

    void on_discoonectBut_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *tcpSocket;


};
#endif // WIDGET_H
