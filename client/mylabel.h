#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QColor>

enum lineColor{white, black, red,
               blue, yellow, green,
               oringe, pink, purple};

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent );
    virtual void paintEvent(QPaintEvent *event) override;
//    void getPositionPredict();
    QColor getColor(int);
    void paintrect();
    int pos[8][4];
    double pre[8][9];

private:
    int cot;
};

#endif // MYLABEL_H
