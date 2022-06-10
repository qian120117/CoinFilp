#include "mycoin.h"
#include "QDebug"

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}
MyCoin::MyCoin(QString coinImg){
    QPixmap pix;
    bool ret = pix.load(coinImg);
    if(!ret){
        qDebug()<<"图片加载失败！";
        return;
    }
    setFixedSize(pix.width(),pix.height());

    setStyleSheet("QPushButton{border:opx;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    //金币翻银币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        pix.load(str);

        setFixedSize(pix.width(),pix.height());
        setStyleSheet("QPushButton{border:opx;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min > this->max){
            this->min = 1;
            this->isanimation =false;
            timer1->stop();
        }
    });
    //银币翻金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str);

        setFixedSize(pix.width(),pix.height());
        setStyleSheet("QPushButton{border:opx;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max < this->min){
            this->max = 8;
            this->isanimation =false;
            timer2->stop();
        }
    });
}

void MyCoin::changFlag(){
    if(this->flag){
        timer1->start(30);
        this->isanimation =true;
        this->flag = false;
    }else{
        timer2->start(30);
        this->isanimation =true;
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isanimation | this->isWin == true){
        return;
    }else{
        QPushButton::mousePressEvent(e);
    }
}
