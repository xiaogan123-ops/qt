#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QStack>
#include <QPair>

struct Cell {
    bool top, right, bottom, left;
    bool visited;
    Cell() : top(true), right(true), bottom(true), left(true), visited(false) {}
};

class MazeWidget : public QWidget {
    Q_OBJECT
public:
    explicit MazeWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void dfsStep(); // 每次 DFS 算法执行一步

private:
    int rows, cols;   // 迷宫行数和列数
    int cellSize;     // 每个单元的像素大小

    QVector<QVector<Cell>> grid; // 迷宫的二维数组
    QStack<QPair<int,int>> stack; // DFS 的栈，存储当前单元的行和列

    int currentRow, currentCol;  // 当前处理的单元
    QTimer* timer;               // 定时器，用于动态更新

    // 辅助函数：判断指定坐标是否在范围内
    bool isValid(int row, int col) {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }
};

#endif // MAZEWIDGET_H
