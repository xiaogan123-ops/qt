#ifndef FOURWINDOW_H
#define FOURWINDOW_H

#include <QMainWindow>
#include"gameman.h"
#include"maze.h"
#include<QMediaPlayer>
#include <QAudioOutput>
#include"settingwindow.h"
namespace Ui {
class FourWindow;
}

class FourWindow : public QMainWindow
{
    Q_OBJECT

public:



    explicit FourWindow(QWidget *parent = nullptr);
    ~FourWindow();
    void paintEvent(QPaintEvent *event);
    void updateMazeData(const QVector<QVector<int>>& data);//更新迷宫数据

private slots:
    void onBackButtonClicked(); // 处理返回上一个界面的按钮点击事件
    void onSpinBoxValueChanged(int value); // 槽函数，用于响应 QSpinBox 的值变化
    void onSpinBoxValueChanged_2(int value);
    void onSpinBoxValueChanged_3(int value);
    void onSpinBoxValueChanged_4(int value);
    void onSpinBoxValueChanged_5(int value);
    void onSpinBoxValueChanged_6(int value);
    void onGenerateMazeClicked();

    void drawMaze();// 绘制迷宫
    void drawMaze1();// 绘制迷宫_2


private:
    Ui::FourWindow *ui;
    Gameman *mpmap;   // 地图管理对象
    int mazeRows;     // 迷宫行数
    int mazeCols;     // 迷宫列数
    int endX;
    int endY;
    int startx;
    int starty;

    Maze *maze;

    QMediaPlayer *mMedia;    // 媒体播放器
    QAudioOutput *audioOutput; // 音频输出

    settingWindow *settingwindow;
};

#endif // FOURWINDOW_H
