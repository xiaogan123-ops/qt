#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"
#include"fourwindow.h"
#include<QMediaPlayer>
#include <QAudioOutput>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override; // 重写 paintEvent 以绘制背景

private slots:
    void onNextButtonClicked(); // 处理跳转到下一个界面的按钮点击事件
    void onAboutButtonClicked();//关于按钮
    void onNextTowButtonClicked();// 制作地图页面
    void onExitButtonClicked(); // 退出按钮的槽函数

private:
    Ui::MainWindow *ui;
    SecondWindow *secondWindow; // SecondWindow 的指针
    FourWindow *fourwindow;

    QMediaPlayer *mMedia;    // 媒体播放器
    QAudioOutput *audioOutput; // 音频输出

};

#endif // MAINWINDOW_H
