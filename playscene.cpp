#include "playscene.h"
#include "QMenuBar"
#include "QPainter"
#include "mypushbutton.h"
#include "QTimer"
#include "QLabel"
#include "mycoin.h"
#include "dataconfig.h"
#include "QtDebug"
#include "QPropertyAnimation"
#include "QSound"

//playScene::playScene(QWidget *parent) : QMainWindow(parent)
//{

//}
playScene::playScene(int levelNum){
    this->levelNum = levelNum;

    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币");

    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    QMenu *startmenu = bar->addMenu("开始");
    QAction *quitAction = startmenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSound *playmusic = new QSound(":/res/ConFlipSound.wav",this);
    QSound *backplaymusic = new QSound(":/res/BackButtonSound.wav",this);
    QSound *winmusic = new QSound(":/res/LevelWinSound.wav",this);


    myPushButton *backbtn = new myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    connect(backbtn,&myPushButton::clicked,[=](){
        backplaymusic->play();
        QTimer::singleShot(200,this,[=](){
           emit this->backChooseScene();
        });
    });

    QLabel *label = new QLabel();
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str = QString("Level: %1").arg(this->levelNum);
    label->setFont(font);
    label->setText(str);
    label->setGeometry(30,this->height()-50,120,50);
    dataConfig mydata;
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            this->gameArray[i][j] = mydata.mData[this->levelNum][i][j];
        }
    }

    QLabel* winlabel = new QLabel();
    QPixmap tmppix;
    tmppix.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setGeometry(0,0,tmppix.width(),tmppix.height());
    winlabel->setPixmap(tmppix);
    winlabel->setParent(this);
    winlabel->move((this->width()-tmppix.width())*0.5,-tmppix.height());

    //翻金币背景
    for(int i=0;i<4;i++){
        for (int j=0;j<4;j++) {
            QPixmap pix = QPixmap(":/res/BoardNode(1).png");
            QLabel *label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*50,200+j*50);
            //创建金币
            QString str;
            if(this->gameArray[i][j]==1){
                str = ":/res/Coin0001.png";
            }else{
                str = ":/res/Coin0008.png";
            }

            MyCoin* coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];
            coinbtn[i][j] = coin;

            connect(coin,&MyCoin::clicked,[=](){
                playmusic->play();
                for (int i=0;i<4;i++) {
                    for (int j=0;j<4;j++) {
                        coinbtn[i][j]->isWin = true;
                    }
                }
                coin->changFlag();
                this->gameArray[i][j] = this->gameArray[i][j]==0 ? 1:0;

                QTimer::singleShot(200,[=](){
                    if(coin->posX+1<=3){
                        coinbtn[coin->posX+1][coin->posY]->changFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY]==0 ? 1:0;
                    }
                    if(coin->posX-1>=0){
                        coinbtn[coin->posX-1][coin->posY]->changFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY]==0 ? 1:0;
                    }
                    if(coin->posY+1<=3){
                        coinbtn[coin->posX][coin->posY+1]->changFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1]==0 ? 1:0;
                    }
                    if(coin->posY-1>=0){
                        coinbtn[coin->posX][coin->posY-1]->changFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1]==0 ? 1:0;
                    }
                    for (int i=0;i<4;i++) {
                        for (int j=0;j<4;j++) {
                            coinbtn[i][j]->isWin = false;
                        }
                    }
                    this->isWin = true;
                    for (int i=0;i<4;i++) {
                        for (int j=0;j<4;j++) {
                            if(this->gameArray[i][j]==0){
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin){
//                        qDebug()<<QString("succeed");
                        for (int i=0;i<4;i++) {
                            for (int j=0;j<4;j++) {
                                coinbtn[i][j]->isWin = true;
                            }
                        }
                        winmusic->play();
                        QPropertyAnimation* animation = new QPropertyAnimation(winlabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                        animation->setEndValue(QRect(winlabel->x(),winlabel->y()+114,winlabel->width(),winlabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });

            });

        }
    }

}

void playScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
