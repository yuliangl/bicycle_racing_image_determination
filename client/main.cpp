#include "widget.h"
#include <QDebug>
#include <QByteArray>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QByteArray b = " 230";
    qDebug()<< "b:"<<b.toInt() + 1;
    w.show();
    return a.exec();
}
