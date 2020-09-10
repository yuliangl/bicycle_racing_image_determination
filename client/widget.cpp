#include <QHostAddress>
#include <QDebug>
#include <QPixmap>
#include <regex>
#include <iostream>
#include <string>
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget),
      array(" ")


{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket;
    tcpSocket->setReadBufferSize(4096);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(on_connected()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(outError(QAbstractSocket::SocketError)));
    bool success = connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(on_ReadyRead()));
    qDebug() << "success is " << success;

    ui->label_status->setText("disconnected");


    for (int i=0; i<8; i++) {
        for (int j=0; j<4; j++) {
            pos[i][j] = 0;
        }
    }
    for (int i=0; i<8; i++) {
        for (int j=0; j<9; j++) {
            pre[i][j] = 0;
        }
    }
}


void Widget::on_pathBut_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,tr("画像"),".",
                                                    tr("Image File(*.png *.jpg *.bmp *.jepg)"));
    ui->lineEdit_path->setText(file_name);
    ui->label_path->setText(file_name);
    if( img.load(file_name) ){
        img.scaled(ui->label_img->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label_img->setScaledContents(true);
        ui->label_img->setPixmap(img);
    }
    else{
        QMessageBox::critical(NULL, "error!", "open a picture failed!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

void Widget::paintEvent(QPaintEvent *event){
    setScaling();
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
    array = tcpSocket->readAll();
//    qDebug()<< "array: " << array;

    getPositionPredict();

    ui->label_img->paintrect();

}

void Widget::on_sendBut_clicked()
{
    QString imagePath = ui->label_path->text();
    QString command = "RUN " + imagePath;
    int res = tcpSocket->write(command.toUtf8().data());
    qDebug() << res << "is sent";
//    qDebug() << " imagePath is " << imagePath;

}

void Widget::getPositionPredict(){
    QString data(array);
//    qDebug()<< "data: "<< data;
    std::string dataStr = data.toStdString();
    std::regex partition(">");
    std::sregex_token_iterator start(dataStr.begin(), dataStr.end(), partition, -1);
    decltype(start) end;
    QString str[2];
    for (int i=0; start != end; ++start,++i)
    {
        str[i] = QString::fromStdString(*start);
        str[i].remove(QChar('<'), Qt::CaseSensitive);
        str[i].remove(QChar('['), Qt::CaseSensitive);
        str[i].remove(QChar(']'), Qt::CaseSensitive);
        str[i].remove(QChar(' '), Qt::CaseSensitive);
    }

    std::string posStr = str[0].toStdString();
    std::string predStr = str[1].toStdString();

    std::regex reg(",");
    std::sregex_token_iterator poStart(posStr.begin(), posStr.end(), reg, -1);
    std::sregex_token_iterator predStart(predStr.begin(), predStr.end(), reg, -1);

    for (int i=0; poStart != end; ++poStart,++i)
    {
        QString tmp = QString::fromStdString(*poStart);
        pos[i/4][i%4] = tmp.toDouble();
//        qDebug() << i <<"pos: " << tmp;
    }

    for (int i=0; predStart!= end; ++predStart,++i)
    {
        QString tmp = QString::fromStdString(*predStart);
        pre[i/9][i%9] = tmp.toDouble();
//        qDebug() << i <<"pre: " << tmp;
    }

}

void Widget::setScaling(){
    double label_x = ui->label_img->size().width();
    double label_y = ui->label_img->size().height();
    double img_x = img.width();
    double img_y = img.height();
    qDebug() << "lx: "<<label_x;
    qDebug() << "ly: "<<label_y;
    qDebug() << "ix: "<<img_x;
    qDebug() << "iy: "<<img_x;

    for(int i=0; i<8; i++){
        ui->label_img->pos[i][0] = (pos[i][0]/img_x)*label_x;
        ui->label_img->pos[i][1] = (pos[i][1]/img_y)*label_y;
        ui->label_img->pos[i][2] = (pos[i][2]/img_x)*label_x;
        ui->label_img->pos[i][3] = (pos[i][3]/img_y)*label_y;
        for (int j=0; j<4; j++){
//            qDebug() << i << ": "<<pos[i][j];
        }
    }
    for (int i=0; i<8; i++){
        for(int j=0; j<9; j++){
    ui->label_img->pre[i][j] = pre[i][j];
        }
    }
}
