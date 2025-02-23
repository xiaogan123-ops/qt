#ifndef MAZE_H
#define MAZE_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include<QStack>
#include<QTimer>


class FourWindow;
class Maze : public QObject
{
    Q_OBJECT
public:
    enum Algorithm {
        DFS, PRIM, Brute_force_DFS,
    }; // 迷宫算法类型

    explicit Maze(QObject *parent = nullptr);
    Maze(int rows, int cols,  QObject *parent = nullptr);
    Maze(int rows, int cols, int startX, int startY, int endX, int endY, Algorithm algorithm, QObject *parent = nullptr);

    void generateMaze();
    bool saveToFile(const QString &filename) const;
    int getRows() const;
    int getCols() const;
    int getstartx() const;
    int getstarty() const;
    int getendx() const;
    int getendy() const;
    QVector<QVector<int>> getmaze();

    void generateMazeDFSVisual(FourWindow* window);
    void generateMazeprimVisual(FourWindow* window);
    void generateMazebfsVisual(FourWindow* window);

    bool loadFromFile(const QString &filename);
    QPair<int, int> findStartPosition();
    QPair<int, int> findEndPosition() const;
    int countAdjacentWalls(int x, int y);

signals:
    void cellChanged(int x, int y, int value); // 新增信号

private:
    bool isValid(int x, int y);
    void removeWall(int x1, int y1, int x2, int y2);

    int rows, cols;
    int startX, startY, endX, endY; //  添加终点坐标作为成员变量
    QVector<QVector<int>> maze;
    const int DX[4] = {0, 0, -1, 1}; // 左 右 上 下
    const int DY[4] = {-1, 1, 0, 0};
    Algorithm algorithmType;

    void generateMazeDFS();
    void generateMazePrim();
    void generateMazeBruteForceDFS();



};

#endif // MAZE_H
