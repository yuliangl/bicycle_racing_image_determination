#include <QHostAddress>
#include <QDebug>
#include <QPixmap>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket;
    tcpSocket->setReadBufferSize(4096);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(on_connected()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(outError(QAbstractSocket::SocketError)));
    bool success = connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(on_ReadyRead()));
    qDebug() << "success is " << success;

}


void Widget::on_pathBut_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,tr("画像"),".",
                                                    tr("Image File(*.png *.jpg *.bmp *.jepg)"));
    ui->lineEdit_path->setText(file_name);
    ui->label_path->setText(file_name);
    QPixmap img;
    if( img.load(file_name) ){
        ui->label_img->setPixmap(img);
    }
    else{
        QMessageBox::critical(NULL, "error!", "open a picture failed!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

Widget::~Widget(){
    delete ui;
}

void Widget::on_connectBut_clicked()
{
    ui->lineEdit_IP->setText("192.168.3.9");
    ui->lineEdit_port->setText("50001");

    QString ip = ui->lineEdit_IP->text();
    qint32 port = ui->lineEdit_port->text().toInt();
    //connect to server
    tcpSocket->connectToHost(QHostAddress(ip), port);
}

void Widget::on_connected(){
    ui->label_status->setText("connect finish");
}

void Widget::on_disconnected(){
    ui->label_status->setText("disconnected ");
}

void Widget::on_discoonectBut_clicked()
{
    tcpSocket->disconnectFromHost();
//	tcpSocket->close();

}
void Widget::outError(QAbstractSocket::SocketError error){
    qDebug() << "connect error is : "<< error;
}

void Widget::on_ReadyRead()
{
    QByteArray array = tcpSocket->readAll();
    int i = 0;
    while (array[i] != '\0') {
        i++;
    }
    qDebug()<< "i: " << i ;

//    ui->label_img->setText(QString(array));
}
void Widget::on_sendBut_clicked()
{
    QString imagePath = ui->label_path->text();
    QString command = "RUN " + imagePath;
    int res = tcpSocket->write(command.toUtf8().data());
    qDebug() << res << "is sent";
    qDebug() << " imagePath is " << imagePath;

}


