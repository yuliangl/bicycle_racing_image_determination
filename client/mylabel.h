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

signals:

};

#endif // MYLABEL_H
