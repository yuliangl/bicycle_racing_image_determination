#include <QPainter>
#include <QDebug>
#include <regex>
#include <iostream>
#include <string>

#include "mylabel.h"

myLabel::myLabel(QWidget *parent) : QLabel(parent), cot(0)
{
}

void myLabel::paintrect(){
    update();
}
void myLabel::paintEvent(QPaintEvent *event){
    QLabel::paintEvent(event);

    for(int i=0; i<8; i++){
//        getPositionPredict();
        QColor linecolor(getColor(i));
        int lineSize = 2;

        QPainter painter(this);
        QPen pen;
        pen.setColor(linecolor);
        pen.setWidth(lineSize);
        painter.setPen(pen);

        painter.drawRect(pos[i][0], pos[i][1], pos[i][2]-pos[i][0], pos[i][3]-pos[i][1]);
    }
    cot++;
    std::cout<< "cot: " << cot <<std::endl;

}

/*
void myLabel::getPositionPredict(){
    QString data(readData);
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
        pos[i/4][i%4] = tmp.toInt();
//        qDebug() << i <<"pos: " << tmp;
    }

    for (int i=0; predStart!= end; ++predStart,++i)
    {
        QString tmp = QString::fromStdString(*predStart);
        pre[i/9][i%9] = tmp.toDouble();
//        qDebug() << i <<"pre: " << tmp;
    }
}
*/

QColor myLabel::getColor(int i){
    std::vector<double> predict;
    for(int j=0; j<9; j++){
        predict.push_back(pre[i][j]);
    }
    std::vector<double>::iterator max = std::max_element(predict.begin(), predict.end());
//    std::cout<< "max" << i << *max <<std::endl;
    int color = std::distance(predict.begin(), max);
//    std::cout<< "color: " << color <<std::endl;
    switch (color) {
        case white: return Qt::white;
        case black: return Qt::black;
        case red: return Qt::red;
        case blue: return Qt::blue;
        case yellow: return Qt::yellow;
        case green: return Qt::green;
        case oringe: return Qt::darkYellow;
        case pink: return Qt::magenta;
        case purple: return Qt::darkMagenta;
    }
}
