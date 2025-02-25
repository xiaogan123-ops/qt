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
{
    ui->setupUi(this);
    setFixedSize(700, 500);



    // 配置音频播放器
    mMedia->setAudioOutput(audioOutput);
    mMedia->setSource(QUrl("qrc:/res/ButtonSound.wav"));
    audioOutput->setVolume(50);

    // 初始化按钮功能
    widget->setWindowFlags(Qt::Window);
    connect(ui->btu2, &QPushButton::clicked, this, &SecondWindow::onNextButtonClicked);
    connect(ui->btu1, &QPushButton::clicked, this, &SecondWindow::onBackButtonClicked);
    connect(ui->btu3,&QPushButton::clicked, this, &SecondWindow::onclicked);

    // 动态绑定迷宫关卡按钮
    for (int level = 2; level <= 16; level++) {
        QString buttonName = QString("btu%1").arg(level + 2); // btu3对应level1, btu4对应level2...

        QPushButton* btn = findChild<QPushButton*>(buttonName);
        if (btn) {
            connect(btn, &QPushButton::clicked, [this, level]() {
                this->hide();
                mMedia->play();
                widget->setMaze(level, maze->getRows(), maze->getCols(),
                                maze->getstartx(), maze->getstarty(),
                                maze->getendx(), maze->getendy());
                widget->show();
            });
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
        painter.drawImage(QRect(0, 0, 700, 500), background);
    } else {
        qDebug() << "Failed to load background image.";
    }
}
