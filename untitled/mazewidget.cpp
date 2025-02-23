#include "MazeWidget.h"
#include <QPainter>
#include <cstdlib>
#include <ctime>

MazeWidget::MazeWidget(QWidget *parent)
    : QWidget(parent),
    rows(20), cols(20), cellSize(20),
    currentRow(0), currentCol(0)
{
    // 初始化迷宫网格
    grid.resize(rows);
    for (int i = 0; i < rows; ++i) {
        grid[i].resize(cols);
    }

    // 设置随机数种子
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // 选择起始点，标记为已访问，并压入栈中
    grid[currentRow][currentCol].visited = true;
    stack.push(qMakePair(currentRow, currentCol));

    // 设置定时器，定时执行 DFS 一步操作（例如每 50 毫秒更新一次）
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MazeWidget::dfsStep);
    timer->start(50);
}

void MazeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);

    // 绘制每个单元
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int x = j * cellSize;
            int y = i * cellSize;

            // 绘制墙
            if (grid[i][j].top)
                painter.drawLine(x, y, x + cellSize, y);
            if (grid[i][j].right)
                painter.drawLine(x + cellSize, y, x + cellSize, y + cellSize);
            if (grid[i][j].bottom)
                painter.drawLine(x, y + cellSize, x + cellSize, y + cellSize);
            if (grid[i][j].left)
                painter.drawLine(x, y, x, y + cellSize);

            // 可选：给已访问的单元填充颜色
            if (grid[i][j].visited) {
                painter.fillRect(x + 1, y + 1, cellSize - 2, cellSize - 2, QColor(200, 200, 255));
            }
        }
    }

    // 高亮显示当前正在处理的单元（例如用红色）
    painter.fillRect(currentCol * cellSize + 1, currentRow * cellSize + 1,
                     cellSize - 2, cellSize - 2, Qt::red);
}

void MazeWidget::dfsStep()
{
    if (stack.isEmpty()) {
        timer->stop(); // DFS 完成
        return;
    }

    // 当前单元为栈顶单元
    QPair<int,int> current = stack.top();
    currentRow = current.first;
    currentCol = current.second;

    // 收集当前单元的所有未访问邻居
    QVector<QPair<int,int>> neighbors;

    // 上邻居
    if (isValid(currentRow - 1, currentCol) && !grid[currentRow - 1][currentCol].visited)
        neighbors.push_back(qMakePair(currentRow - 1, currentCol));
    // 右邻居
    if (isValid(currentRow, currentCol + 1) && !grid[currentRow][currentCol + 1].visited)
        neighbors.push_back(qMakePair(currentRow, currentCol + 1));
    // 下邻居
    if (isValid(currentRow + 1, currentCol) && !grid[currentRow + 1][currentCol].visited)
        neighbors.push_back(qMakePair(currentRow + 1, currentCol));
    // 左邻居
    if (isValid(currentRow, currentCol - 1) && !grid[currentRow][currentCol - 1].visited)
        neighbors.push_back(qMakePair(currentRow, currentCol - 1));

    if (!neighbors.isEmpty()) {
        // 随机选择一个未访问邻居
        int idx = std::rand() % neighbors.size();
        QPair<int,int> next = neighbors[idx];
        int nextRow = next.first;
        int nextCol = next.second;

        // 删除当前单元与选择单元之间的墙
        if (nextRow < currentRow) { // 上方邻居
            grid[currentRow][currentCol].top = false;
            grid[nextRow][nextCol].bottom = false;
        } else if (nextRow > currentRow) { // 下方邻居
            grid[currentRow][currentCol].bottom = false;
            grid[nextRow][nextCol].top = false;
        } else if (nextCol < currentCol) { // 左侧邻居
            grid[currentRow][currentCol].left = false;
            grid[nextRow][nextCol].right = false;
        } else if (nextCol > currentCol) { // 右侧邻居
            grid[currentRow][currentCol].right = false;
            grid[nextRow][nextCol].left = false;
        }

        // 标记邻居为已访问并压入栈中
        grid[nextRow][nextCol].visited = true;
        stack.push(qMakePair(nextRow, nextCol));
    } else {
        // 如果没有未访问邻居，则回溯
        stack.pop();
    }

    // 更新界面，触发 paintEvent 重绘
    update();
}
