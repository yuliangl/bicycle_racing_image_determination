#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent );
    virtual void paintEvent(QPaintEvent *event) override;
    void getPositionPredict();

private:
    int pos[8][4];
    double pre[8][9];
};

#endif // MYLABEL_H
