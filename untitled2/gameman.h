#ifndef GAMEMAN_H
#define GAMEMAN_H

#include <QObject>
#include <QPainter>
#include <QVector>
#include"maze.h"

class Gameman : public QObject
{
    Q_OBJECT

public:
    explicit Gameman(QObject *parent = nullptr);
    ~Gameman();

    // 绘制地图
    void paint(QPainter* _p, QPoint _pos);

    // 初始化迷宫数据
    bool InitByData(const QVector<QVector<int>>& data);

    // 判断是否是墙
    bool isWall(int row, int col) const;

    // 获取迷宫单元格的值
    int getCell(int row, int col) const;

    // 设置迷宫单元格的值
    void setCell(int row, int col, int value);

    // 标记路径
    void markPath(int row, int col);

    // 清除所有路径标记
    void resetMaze();

    // 重置迷宫
    void reset();

    // 清理迷宫数据
    void clear();



    void GenerateMazeDFS();
    int mrow;  // 行数
    int mcol;  // 列数

    bool isValid(int row, int col) const;
    bool isRoad(int row, int col) const;




private:




    QVector<QVector<int>> mpArr;  // 使用 QVector 存储迷宫数据，替换裸指针
    Maze *maze; // Maze 类的实例
    int endX = -1;
    int endY = -1;

};

#endif // GAMEMAN_H
