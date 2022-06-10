#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);

    MyCoin(QString coinImg);

    int posX;
    int posY;
    int flag;

    void changFlag();

    QTimer* timer1;
    QTimer* timer2;
    int min = 1;
    int max = 8;

    bool isanimation=false;
    void mousePressEvent(QMouseEvent *);
    bool isWin=false;

signals:

};

#endif // MYCOIN_H
