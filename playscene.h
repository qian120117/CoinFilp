#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class playScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit playScene(QWidget *parent = nullptr);
    playScene(int levelNum);

    int levelNum;

    void paintEvent(QPaintEvent *);

    int gameArray[4][4];

    MyCoin* coinbtn[4][4];

    bool isWin;
signals:
    void backChooseScene();

};

#endif // PLAYSCENE_H
