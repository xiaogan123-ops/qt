#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include <QPushButton>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , secondWindow(new SecondWindow(this))
    ,fourwindow(new FourWindow(this))
    ,mMedia(new QMediaPlayer(this))
    ,audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);
    setFixedSize(700, 500);

     // 连接按钮信号与槽函数
    connect(ui->btu2, &QPushButton::clicked, this, &MainWindow::onNextButtonClicked);
    connect(ui->btu3, &QPushButton::clicked, this,&MainWindow::onExitButtonClicked);
    connect(ui->btu1, &QPushButton::clicked, this, &MainWindow::onAboutButtonClicked);
    connect(ui->btu4,&QPushButton::clicked,this,&MainWindow::onNextTowButtonClicked);

    // 配置音频设置
    mMedia->setAudioOutput(audioOutput);
    mMedia->setSource(QUrl("qrc:/res/ButtonSound.wav"));
    audioOutput->setVolume(50);




}

void MainWindow::onNextTowButtonClicked(){
    this->hide();
    fourwindow->show();
    mMedia->play();

}

// 退出按钮点击处理
void MainWindow::onExitButtonClicked(){
    mMedia->play();
    connect(mMedia, &QMediaPlayer::playbackStateChanged, this, [this](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::StoppedState) {
            qApp->quit(); // 音效播放完成后退出
        }
    });

}
void MainWindow::onNextButtonClicked()
{
    this->hide();// 隐藏主窗口
    secondWindow->show();
    mMedia->play();
}

// 释放资源
MainWindow::~MainWindow()
{
    delete ui;
    delete secondWindow;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // 标记未使用参数

    QPainter painter(this);

    // Draw background
    QImage background("://res/c.jpg");
    if (!background.isNull()) {
        painter.drawImage(QRect(0, 0, 700, 500), background);
    } else {
        qDebug() << "Failed to load background image.";
    }
}

void MainWindow::onAboutButtonClicked()
{
    mMedia->play();
    QMessageBox::information(this, "关于游戏",
                             "Code by Xiaogan\n\n"
                             "Language: C++ and Qt\n\n"
                             "Time: 2025-2");

}
