#include <QPainter>

#include "mylabel.h"

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{

}
void myLabel::paintEvent(QPaintEvent *event){
    QLabel::paintEvent(event);

    QPoint startPoint(0,0);
    QPoint endPoint(0,0);
    QColor lineColor(Qt::red);
//    int lineSize = 2;


    QPainter painter(this);
    QPen pen;
    pen.setColor(lineColor);
//    pen.setWidth(lineSize);
    painter.setPen(pen);
    painter.drawRect(QRect(startPoint.x(), startPoint.y(),
                           endPoint.x()-startPoint.x(), endPoint.y()-startPoint.y()));

}
