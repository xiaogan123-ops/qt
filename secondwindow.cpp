#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "widget.h"
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QIntValidator>
#include <QMessageBox> // 用于错误提示
#include <QStandardPaths>
#include<QDir>
#include<QFileDialog>
#include<QVBoxLayout>
#include<QScrollArea>
SecondWindow::SecondWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SecondWindow)
    , widget(new Widget(this))
    , maze(new Maze())
    ,mMedia(new QMediaPlayer(this))
    ,audioOutput(new QAudioOutput(this))
    ,settingwindow(settingWindow::instance(this))
{
    ui->setupUi(this);
    setFixedSize(850, 600);



    // 配置音频播放器
    mMedia->setAudioOutput(audioOutput);
    mMedia->setSource(QUrl("qrc:/res/ButtonSound.wav"));
    audioOutput->setVolume(50);
    settingwindow->registerAudioOutput(audioOutput);

    // 初始化按钮功能
     widget->setWindowFlags(Qt::Window);
    connect(ui->btu2, &QPushButton::clicked, this, &SecondWindow::onNextButtonClicked);
    connect(ui->btu1, &QPushButton::clicked, this, &SecondWindow::onBackButtonClicked);
    connect(ui->btu3,&QPushButton::clicked, this, &SecondWindow::onclicked);



    m_unlockedLevels.clear();
    m_unlockedLevels.insert(1, true);  // 默认解锁第三关（显示为第一关）
    for(int level = 2; level <= 18; ++level) {
        m_unlockedLevels.insert(level, false);
    }
    // 动态绑定迷宫关卡按钮
    for (int level = 3 ; level <= 17; level++) { // 处理1-15关

        QString buttonName = QString("btu%1").arg(level + 2);
        QPushButton* btn = findChild<QPushButton*>(buttonName);
        if (level == 2) { // 调试第0关（实际level2）
            qDebug() << "找到按钮指针：" << btn;
        }
        if (btn) {
            // 设置初始解锁状态
            // bool isUnlocked = m_unlockedLevels.value(level, false);
            // btn->setEnabled(isUnlocked);
            // btn->setIcon(isUnlocked ? QIcon(":/res/1.png") : QIcon(":/res/6.png"));
            // btn->setIconSize(QSize(40, 40));

            // 连接信号
            connect(btn, &QPushButton::clicked, [this, level]() {
                this->hide();
                mMedia->play();
                 int t=level-1;

                widget->setMaze(t, maze->getRows(), maze->getCols(),
                                maze->getstartx(), maze->getstarty(),
                                maze->getendx(), maze->getendy());
                widget->show();
            });
        }
    }


    // ui->btu4->setEnabled(false);
    //  ui->btu4->setIcon(false ? QIcon() : QIcon(":/res/6.png"));
    //  ui->btu4->setIconSize(QSize(40, 40));

    connect(widget, &Widget::levelUnlocked, this, [this](int level){
        if (level >= 1 && level <= 17) {
            if(level==2){
                level+=1;
            }
            m_unlockedLevels.insert(level, true);
            qDebug() << "解锁关卡：" << level;
            updateLevelButtons();
        }
    });



}
void SecondWindow::updateLevelButtons() {
    for (int level = 3; level <= 17; level++) {
        QString buttonName = QString("btu%1").arg(level + 2);
        QPushButton* btn = findChild<QPushButton*>(buttonName);
        if (btn) {

            bool isUnlocked = m_unlockedLevels.value(level, false);
            qDebug()<<isUnlocked;
            btn->setEnabled(isUnlocked);
            btn->setIcon(isUnlocked ? QIcon() : QIcon(":/res/6.png"));
            btn->setIconSize(QSize(40, 40));
        }
    }
}
// 返回 MainWindow
void SecondWindow::onBackButtonClicked()
{
    qDebug() << "Back button clicked";
    this->hide();                      // 隐藏当前窗口
    if (parentWidget()) {
        parentWidget()->show();
    } else {
        qDebug() << "Parent widget is null";
    }
    mMedia->play();

}

void SecondWindow::onNextButtonClicked(){

    this->hide();
    widget->setMazeParameters( maze->getRows(), maze->getCols(),
                              maze->getstartx(), maze->getstarty(),
                              maze->getendx(), maze->getendy());
    widget->show();
    mMedia->play();

}
void SecondWindow::onclicked(){
    this->hide();
    widget->setMaze(1,maze->getRows(),maze->getCols(),maze->getstartx(),maze->getstarty(),maze->getendx(),maze->getendy());
    widget->show();
    mMedia->play();
}
SecondWindow::~SecondWindow()
{
    delete maze; // 释放 Maze 资源
    delete ui;
}

// 绘制窗口背景
void SecondWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制背景
    QImage background("://res/background2.jpg");
    if (!background.isNull()) {
        painter.drawImage(QRect(0, 0, 850, 600), background);
    } else {
        qDebug() << "Failed to load background image.";
    }
}
