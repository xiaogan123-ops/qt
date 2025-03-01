#ifndef MAZE_H
#define MAZE_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include<QStack>
#include<QTimer>
#include <random>
#include <QSet>

class FourWindow;
class Maze : public QObject
{
    Q_OBJECT
public:
    enum Algorithm {
        Graph_DFS, PRIM, Kruskal,
    }; // 迷宫算法类型

    explicit Maze(QObject *parent = nullptr);
    Maze(int rows, int cols,  QObject *parent = nullptr);
    Maze(int rows, int cols, int startX, int startY, int endX, int endY, Algorithm algorithm, QObject *parent = nullptr);

    bool saveToFile(const QString &filename) const;
    int getRows() const;
    int getCols() const;
    int getstartx() const;
    int getstarty() const;
    int getendx() const;
    int getendy() const;
    QVector<QVector<int>> getmaze();

    void generateMazeDFSVisual(FourWindow* window); // DFS可视化生成
    void generateMazeprimVisual(FourWindow* window);// Prim算法可视化
    void generateMazeKruskalVisual(FourWindow* window);// Kruskal算法可视化

    bool loadFromFile(const QString &filename); // 从文件加载迷宫

    QPair<int, int> findStartPosition();// 查找起点位置
    QPair<int, int> findEndPosition() const;// 查找终点位置
    int countAdjacentWalls(int x, int y);  // 计算相邻墙数

signals:
    void cellChanged(int x, int y, int value);  // 单元格变化信号

private:
    bool isValid(int x, int y);
    void removeWall(int x1, int y1, int x2, int y2);

    int rows, cols;
    int startX, startY, endX, endY;
    QVector<QVector<int>> maze;// 迷宫数据存储（二维数组）
    const int DX[4] = {1, 0, -1, 0};
    const int DY[4] = {0, -1, 0, 1};
    Algorithm algorithmType;

    struct Edge {
        int x1, y1, x2, y2;  // 相邻的两个单元格
        int wallX, wallY;    // 需要打破的墙的位置
    };


    // 并查集操作
    int findParent(QVector<int>& parent, int cell);
    void unionSets(QVector<int>& parent, QVector<int>& rank, int x, int y);// 合并集合



};

#endif // MAZE_H
