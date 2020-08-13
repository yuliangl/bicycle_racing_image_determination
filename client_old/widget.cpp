#include <QHostAddress>
#include <QDebug>

#include "widget.h"
#include "ui_widget.h"
#include "dialog.h"
#include "ui_dialog.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    dialog = new Dialog();
    label_img = new myLabel(this);

    tcpSocket->setReadBufferSize(4096);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(on_connected()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(outError(QAbstractSocket::SocketError)));
    bool success = connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(on_ReadyRead()));
    qDebug() << "success is " << success;

    connect(label_img, SIGNAL(startPointSignal(QPoint)),
            this, SLOT(startPointSlot(QPoint)));
    connect(label_img, SIGNAL(stopPointSignal(QPoint)),
            this, SLOT(stopPointSlot(QPoint)));
    label_img->setStyleSheet("border:1px solid rgb(0, 0, 0)");
    label_img->setMaximumSize(3000, 3000);
    label_img->setMinimumSize(600, 350);

    ui->label_layout->addWidget(label_img);

    connect(ui->pathBut, SIGNAL(clicked(bool)),
            this, SLOT(openPathSlot()));
    connect(ui->lineEdit_start_x, SIGNAL(textChanged(QString)),
            this, SLOT(pointTextChangeSlot(QString)));
    connect(ui->lineEdit_start_y, SIGNAL(textChanged(QString)),
            this, SLOT(pointTextChangeSlot(QString)));
    connect(ui->lineEdit_size_w, SIGNAL(textChanged(QString)),
            this, SLOT(pointTextChangeSlot(QString)));
    connect(ui->lineEdit_size_h, SIGNAL(textChanged(QString)),
            this, SLOT(pointTextChangeSlot(QString)));

}

void Widget::on_connectBut_clicked(){

    QString ip = "192.168.3.9";
    qint32 port = 50001;
    ui->lineEdit_IP->setText("192.168.3.9");
    ui->lineEdit_port->setText("50001");

    //connect to server
    tcpSocket->connectToHost(QHostAddress(ip), port);
    dialog->show();
}

void Widget::on_sendBut_clicked(){
    QString imagePath = ui->label_path->text();
    int res = tcpSocket->write(imagePath.toUtf8().data());
    qDebug() << res << "is sent";
    qDebug() << " imagePath is " << imagePath;
}


void Widget::on_connected(){
    dialog->ui->textEdit_read->setText("connect finish");
}

void Widget::on_disconnected(){
    dialog->ui->textEdit_read->setText("disconnected");
}

void Widget::outError(QAbstractSocket::SocketError error){
    qDebug() << "connect error is : "<< error;
}

void Widget::on_discoonectBut_clicked(){
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}

void Widget::on_ReadyRead()
{
//    if(tcpSocket->waitForReadyRead() == false){
//        qDebug() <<"Server does not response!";
//        return;
//    }
    qDebug() << "readyread";
    QByteArray array = tcpSocket->readAll();
    dialog->ui->textEdit_read->append(QString(array));
}

void Widget::pointTextChangeSlot(QString){
    if(capture != NULL){
        double Start_x = ui->lineEdit_start_x->text().toInt();
        double Start_y = ui->lineEdit_start_y->text().toInt();
        double ROI_w = ui->lineEdit_size_w->text().toInt();
        double ROI_h = ui->lineEdit_size_h->text().toInt();
        double label_size_w = label_img->size().width();
        double label_size_h = label_img->size().height();
        double img_w = capture->get(3);
        double img_h = capture->get(4);
        double Stop_x = Start_x+ROI_w;
        double Stop_y = Start_y+ROI_h;

        int label_start_x = (Start_x/img_w)*label_size_w;
        int label_start_y = (Start_y/img_h)*label_size_h;
        int label_stop_x = (Stop_x/img_w)*label_size_w;
        int label_stop_y = (Stop_y/img_h)*label_size_h;

        label_img->paintRect(QPoint(label_start_x,label_start_y),
                            QPoint(label_stop_x,label_stop_y) );
    }
    else{
        QMessageBox::critical(NULL, "error!", "open a picture please!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
}

void Widget::startPointSlot(QPoint p){
    startPoint = p;

    if(capture!=NULL){

        double label_size_w = label_img->size().width();
        double label_size_h = label_img->size().height();
        double img_w = capture->get(3);
        double img_h = capture->get(4);
        double point_x = p.x();
        double point_y = p.y();

        int ROI_x = (point_x/label_size_w)*img_w;
        int ROI_y = (point_y/label_size_h)*img_h;

        ui->lineEdit_start_x->setText(QString::number(ROI_x));
        ui->lineEdit_start_y->setText(QString::number(ROI_y));
    }
    else{
        ui->lineEdit_start_x->setText(QString::number(0));
        ui->lineEdit_start_y->setText(QString::number(0));
    }
}

void Widget::stopPointSlot(QPoint p){
    if(capture!=NULL){
        double label_size_w = label_img->size().width();
        double label_size_h = label_img->size().height();
        double img_w = capture->get(3);
        double img_h = capture->get(4);
        double point_End_x = p.x();
        double point_End_y = p.y();
        double point_Start_x = startPoint.x();
        double point_Start_y = startPoint.y();

        int ROI_w = ((point_End_x-point_Start_x)/label_size_w)*img_w;
        int ROI_h = ((point_End_y-point_Start_y)/label_size_h)*img_h;


        ui->lineEdit_size_w->setText(QString::number(ROI_w));
        ui->lineEdit_size_h->setText(QString::number(ROI_h));
    }
    else{
        ui->lineEdit_size_w->setText(QString::number(0));
         ui->lineEdit_size_h->setText(QString::number(0));
    }

}

void Widget::openPathSlot(){
    QString file_name = QFileDialog::getOpenFileName(this,tr("画像"),".",
                                                    tr("Image File(*.png *.jpg *.bmp *.jepg)"));
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly))
    {

        return;
    }
    else{
        ui->lineEdit_path->setText(file_name);
        capture = new cv::VideoCapture();
        capture->open(file_name.toStdString());
        cv::Mat frame;
        bool ret = capture->read(frame);
        if(!ret){
            QMessageBox::critical(NULL, "error!", "open a picture failed!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }

        show_img(frame,label_img);
        ui->label_path->setText(QString("RUN ") + file_name);
    }
}

void Widget::show_img(cv::Mat image, QLabel *label){
    cv::cvtColor(image, image, CV_BGR2RGB);
    QImage img =  QImage((const unsigned char*)(image.data),image.cols,image.rows,
                         image.cols*image.channels(),
                         QImage::Format_RGB888).scaled(label->width(), label->height());

     label->clear();
     label->setPixmap(QPixmap::fromImage(img));
}

Widget::~Widget()
{
    delete ui;
}




