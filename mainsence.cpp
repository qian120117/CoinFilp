#include "mainsence.h"
#include "ui_mainsence.h"
#include "QPainter"
#include "mypushbutton.h"
#include "QTimer"
#include <QSound>

MainSence::MainSence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainSence)
{
    ui->setupUi(this);

    setFixedSize(320,588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("翻金币主场景");

    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    QSound *startmusic = new QSound(":/res/TapButtonSound.wav",this);
    myPushButton *startbtn = new myPushButton(":/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width() * 0.5 - startbtn->width() * 0.5,this->height() * 0.7);
    chooselevelscene = new ChooseLevelScene;
    connect(chooselevelscene,&ChooseLevelScene::backMainScene,this,[=](){
        this->setGeometry(chooselevelscene->geometry());
        chooselevelscene->hide();
        this->show();
    });

    connect(startbtn,&myPushButton::clicked,[=](){
        startmusic->play();
       startbtn->zoom1();
       startbtn->zoom2();
       chooselevelscene->setGeometry(this->geometry());
       QTimer::singleShot(200,this,[=](){
           this->hide();
           chooselevelscene->show();
       });

    });

}

void MainSence::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //背景图
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);
    painter.drawPixmap(10,30,pix);
}

MainSence::~MainSence()
{
    delete ui;
}

