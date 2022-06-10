#include "chooselevelscene.h"
#include "QMenuBar"
#include "QPainter"
#include "mypushbutton.h"
#include "QDebug"
#include "QTimer"
#include "QLabel"
#include "QSound"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡场景");

    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    QMenu *startmenu = bar->addMenu("开始");
    QAction *quitAction = startmenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSound *selectmusic = new QSound(":/res/TapButtonSound.wav",this);
    QSound *backmusic = new QSound(":/res/BackButtonSound.wav",this);
    myPushButton *backbtn = new myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    connect(backbtn,&myPushButton::clicked,[=](){
        backmusic->play();
        QTimer::singleShot(200,this,[=](){
           emit this->backMainScene();
        });

    });

    for (int i=0;i<20;i++) {
        myPushButton *menubtn = new myPushButton(":/res/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(20+i%4*70,130+i/4*70);

        connect(menubtn,&myPushButton::clicked,[=](){
            selectmusic->play();
            qDebug()<<QString("选择了第%1关").arg(i+1);
            this->hide();
            playscene = new playScene(i+1);
            playscene->setGeometry(this->geometry());
            playscene->show();
            connect(playscene,&playScene::backChooseScene,[=](){
                this->setGeometry(playscene->geometry());
                this->show();
                delete playscene;
                playscene = NULL;
            });
        });

        QLabel *label = new QLabel();
        label->setParent(this);
        label->setFixedSize(menubtn->width(),menubtn->height());
        label->setText(QString::number(1+i));
        label->move(20+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
