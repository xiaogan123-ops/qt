#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include "widget.h"
#include"maze.h"
#include<QMediaPlayer>
#include <QAudioOutput>
#include"settingwindow.h"
#include <QMap>
QT_BEGIN_NAMESPACE
namespace Ui { class SecondWindow; }
QT_END_NAMESPACE

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);

    ~SecondWindow();
    void updateLevelButtons();


protected:
    void paintEvent(QPaintEvent *event) override; // 绘制背景

private slots:
    void onNextButtonClicked(); // 处理跳转到下一个界面的按钮点击事件
    void onBackButtonClicked(); // 处理返回上一个界面的按钮点击事件
    void onclicked();

private:
    Maze *maze;
    Ui::SecondWindow *ui;
    Widget *widget; // Widget 的指针
    QMediaPlayer *mMedia;    // 媒体播放器
    QAudioOutput *audioOutput; // 音频输出

    settingWindow *settingwindow;
     QMap<int, bool> m_unlockedLevels; // 添加关卡状态存储
};

#endif // SECONDWINDOW_H
