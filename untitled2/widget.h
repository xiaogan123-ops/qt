#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "gameman.h"
#include "role.h"
#include<QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>
#include"settingwindow.h"
#include "monster.h"
#include<QMutex>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void loadMazeFromFile(const QString &filePath); // 加载迷宫文件
    void setMazeParameters(int rows, int cols, int startX, int startY, int endX, int endY); // 设置迷宫参数
    void moveRole(int dRow, int dCol);// 移动角色

    void markPathOnMaze(const QVector<QPair<int, int>>& path);// 标记路径
    void resetMazePathMarks();// 清除路径标记

    void setMaze(int level, int rows, int cols, int startX, int startY, int endX, int endY);// 设置迷宫参数_2
    void resetGame1(int level);// 重置游戏状态

    bool findPathDFS(QList<QPoint>& path);// DFS寻路算法

    void levelComplete();
    QMutex moveMutex;
    int mazeRows;     // 迷宫行数
    int mazeCols;     // 迷宫列数
    void handleGameFailure();

protected:
    void paintEvent(QPaintEvent *event) override;  // 绘制事件
    void keyPressEvent(QKeyEvent *event) override; // 键盘事件
    void closeEvent(QCloseEvent *event) override;  // 关闭事件

private slots:
    void moveMonster();
    void checkCollision();
private slots:
    void updateMonster(); // 定时更新怪物
private:
    Ui::Widget *ui;
    Gameman *mpmap;   // 地图管理对象
    Role *mrole;      // 角色对象
    QTimer *mtime;    // 计时器
    bool gameWon;     // 游戏胜利标志
    int startX;       // 起点行坐标
    int startY;       // 起点列坐标
    int endX;         // 终点行坐标
    int endY;         // 终点列坐标

    void resetGame();       // 重置游戏
    void collision(int dRow, int dCol); // 检测碰撞

    QList<QPoint> solutionPath; // 存储找到的路径
    bool showingPath = false;   // 是否正在显示路径


    QMediaPlayer *mMedia;    // 媒体播放器
    QMediaPlayer *mMedia_2;    // 媒体播放器

    QAudioOutput *audioOutput; // 音频输出
    QAudioOutput *audioOutput_2; // 按钮音效的音频输出

    QMediaPlayer *mMedia_3;    // 媒体播放器
    QAudioOutput *audioOutput_3; // 音频输出

    QMediaPlayer *mMedia_4;    // 媒体播放器
    QAudioOutput *audioOutput_4; // 音频输出

    bool showVictory;     // 显示胜利动画标志
    qreal victoryScale;    // 胜利动画缩放比例
    QTimer* victoryTimer;    // 胜利动画定时器
    bool victorySoundPlayed; // 新增成员变量

    qreal failureScale;   // 失败动画缩放比例
    QTimer* failureTimer_2;   // 失败动画定时器
    bool failure_soundPlayed_2; // 新增成员变量

    settingWindow *settingwindow;
     int currentLevel = 0; // 记录当前正在玩的关卡


     Monster* mmonster = nullptr;
     QTimer* monsterTimer = nullptr;  // 定时器用于怪物移动


signals:
    void back(); // 返回信号
     void levelUnlocked(int level);

private slots:
    void onBackButtonClicked(); // 返回按钮点击事件
    void onNoSolutionButtonClicked();//无解按钮点击事件
    void onAutoPathButtonClicked();  // 自动寻径按钮
};

#endif // WIDGET_H
