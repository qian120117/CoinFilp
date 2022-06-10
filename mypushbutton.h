#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit myPushButton(QWidget *parent = nullptr);

    myPushButton(QString normalImg,QString pressImg = "");

    QString normalImg;
    QString pressImg;

    void zoom1();
    void zoom2();

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:

};

#endif // MYPUSHBUTTON_H
