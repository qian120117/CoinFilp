#include "mypushbutton.h"
#include "QDebug"
#include "QPropertyAnimation"
//myPushButton::myPushButton(QWidget *parent) : QWidget(parent)
//{

//}
myPushButton::myPushButton(QString normalImg,QString pressImg){
    this->pressImg = pressImg;
    this->normalImg = normalImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret){
        qDebug()<<"图片加载失败！";
    }
    setFixedSize(pix.width(),pix.height());

    setStyleSheet("QPushButton{border:opx;}");

    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(),pix.height()));
}

void myPushButton::zoom1(){
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void myPushButton::zoom2(){
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void myPushButton::mousePressEvent(QMouseEvent *e){
    if(this->pressImg != ""){
        QPixmap pix;
        bool ret = pix.load(pressImg);
        if(!ret){
            qDebug()<<"图片加载失败！";
            return;
        }
        setFixedSize(pix.width(),pix.height());

        setStyleSheet("QPushButton{border:opx;}");

        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void myPushButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressImg != ""){
        QPixmap pix;
        bool ret = pix.load(normalImg);
        if(!ret){
            qDebug()<<"图片加载失败！";
            return;
        }
        setFixedSize(pix.width(),pix.height());

        setStyleSheet("QPushButton{border:opx;}");

        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
