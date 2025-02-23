#include "maze.h"
#include <algorithm>
#include <random>
#include <QDebug>
#include <QStack>
#include <QRandomGenerator>
#include <QThread>
#include "fourwindow.h"
#include<QApplication>
#include<QQueue>
#include <algorithm>
Maze::Maze(QObject *parent)
    : QObject(parent), rows(0), cols(0) {

}
Maze::Maze(int rows, int cols,QObject *parent)
    : QObject(parent), rows(rows), cols(cols) {
    maze = QVector<QVector<int>>(rows, QVector<int>(cols, 1));
}
Maze::Maze(int rows, int cols, int startX, int startY, int endX, int endY, Algorithm algorithm, QObject *parent)
    : QObject(parent), rows(rows), cols(cols), startX(startX), startY(startY), endX(endX), endY(endY), algorithmType(algorithm)

{
    // 初始化迷宫，1=墙壁, 0=路径
    this->startX = qBound(0, startX, rows - 1);
    this->startY = qBound(0, startY, cols - 1);
    this->endX = qBound(0, endX, rows - 1);
    this->endY = qBound(0, endY, cols - 1);
    maze = QVector<QVector<int>>(rows, QVector<int>(cols, 1));

}

// 统一调用生成迷宫的方法
void Maze::generateMaze()
{
    switch (algorithmType) {
    case DFS:
        generateMazeDFS();
        break;
    case PRIM:
        generateMazePrim();
        break;
    case Brute_force_DFS:
        generateMazeBruteForceDFS();
        break;
    }
    // **确保终点仍然存在**
    maze[endX][endY] = 2;

}

// **1️⃣ 深度优先搜索（DFS）算法**
void Maze::generateMazeDFS()
{
    QStack<QPair<int, int>> stack;
    stack.push({startX, startY});
    maze[startX][startY] = 0; // 标记起点为路径

    std::random_device rd;
    std::mt19937 g(rd());

    while (!stack.isEmpty()) {
        int x = stack.top().first;
        int y = stack.top().second;
        QVector<int> directions = {0, 1, 2, 3};
        std::shuffle(directions.begin(), directions.end(), g);

        bool moved = false;
        for (int dir : directions) {
            int nx = x + DX[dir] * 2;
            int ny = y + DY[dir] * 2;

            if (isValid(nx, ny)) {
                removeWall(x, y, nx, ny);
                maze[nx][ny] = 0;
                stack.push({nx, ny});
                moved = true;
                break;
            }
        }

        if (!moved) {
            stack.pop();
        }
    }
    // **保证终点至少有一条路径**

    for (int i = 0; i < 4; ++i) {
        int nx = endX + DX[i];
        int ny = endY + DY[i];

        if (isValid(nx, ny) && maze[nx][ny] == 0) {

            break;
        }
    }



    // **确保终点**
    maze[endX][endY] = 2;
}

// **2️ 随机 Prim 算法**
void Maze::generateMazePrim()
{
    // 确保迷宫尺寸为奇数
    if (rows % 2 == 0) rows--;
    if (cols % 2 == 0) cols--;
    maze = QVector<QVector<int>>(rows, QVector<int>(cols, 1)); // 1=墙

    struct Point { int x, y; };
    QList<Point> wallList;

    // 随机选择起点（确保是奇数坐标）
    int startCol = 2 * QRandomGenerator::global()->bounded((cols-1)/2) + 1;
    int startRow = 2 * QRandomGenerator::global()->bounded((rows-1)/2) + 1;
    maze[startRow][startCol] = 0; // 设为路径

    // 将起点周围的墙加入列表
    auto pushSurroundingWalls = [&](int x, int y) {
        const int dx[] = {-1, 0, 1, 0};
        const int dy[] = {0, -1, 0, 1};
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && maze[ny][nx] == 1) {
                wallList.append({nx, ny});
            }
        }
    };
    pushSurroundingWalls(startCol, startRow);

    while (!wallList.isEmpty()) {
        // 随机选择一堵墙
        if (wallList.isEmpty()) break; // 如果列表为空，直接退出

        // 使用显式类型转换
        int index = QRandomGenerator::global()->bounded(static_cast<quint32>(wallList.size()));
        Point wall = wallList.takeAt(index);

        // 寻找墙两侧的单元格
        Point oppositeCell = {-1, -1};
        const int dx[] = {-1, 0, 1, 0};
        const int dy[] = {0, -1, 0, 1};
        for (int i = 0; i < 4; ++i) {
            int ax = wall.x + dx[i];
            int ay = wall.y + dy[i];
            int bx = wall.x - dx[i];
            int by = wall.y - dy[i];

            if (ax >= 0 && ax < cols && ay >= 0 && ay < rows &&
                bx >= 0 && bx < cols && by >= 0 && by < rows)
            {
                bool aPass = maze[ay][ax] == 0;
                bool bPass = maze[by][bx] == 0;

                if (aPass != bPass) { // 只有一侧是通路
                    oppositeCell = aPass ? Point{bx, by} : Point{ax, ay};
                    break;
                }
            }
        }

        // 如果找到有效单元格
        if (oppositeCell.x != -1 && oppositeCell.y != -1 &&
            maze[oppositeCell.y][oppositeCell.x] == 1)
        {
            // 打通墙和对面单元格
            maze[wall.y][wall.x] = 0;
            maze[oppositeCell.y][oppositeCell.x] = 0;

            // 将新单元格周围的墙加入列表
            pushSurroundingWalls(oppositeCell.x, oppositeCell.y);
        }
    }

    // 设置起点和终点
    maze[startY][startX] = 3;
    maze[endY][endX] = 2;

}

// **2️⃣ 暴力深度优先搜索（Brute-force DFS）算法**
void Maze::generateMazeBruteForceDFS()
{
    // 使用递归方式进行暴力DFS生成迷宫
    QStack<QPair<int, int>> stack;
    stack.push({startX, startY});
    maze[startX][startY] = 0;  // 标记起点为路径

    std::random_device rd;
    std::mt19937 g(rd());

    // 暴力DFS的方向（右，下，左，上）
    const int DX[] = {1, 0, -1, 0};
    const int DY[] = {0, 1, 0, -1};

    while (!stack.isEmpty()) {
        int x = stack.top().first;
        int y = stack.top().second;

        QVector<int> directions = {0, 1, 2, 3};  // 随机化方向
        std::shuffle(directions.begin(), directions.end(), g);

        bool moved = false;
        for (int dir : directions) {
            int nx = x + DX[dir] * 2;
            int ny = y + DY[dir] * 2;

            if (isValid(nx, ny)) {
                removeWall(x, y, nx, ny);  // 移除当前单元和新单元之间的墙
                maze[nx][ny] = 0;  // 标记新单元为路径
                stack.push({nx, ny});  // 将新单元推入栈中
                moved = true;
                break;
            }
        }

        if (!moved) {
            stack.pop();  // 如果没有找到新路径，则回退
        }
    }

    // 确保终点设置正确
    maze[endX][endY] = 2;
}

// **辅助函数**
bool Maze::isValid(int x, int y)
{
    return x > 0 && x < rows - 1 && y > 0 && y < cols - 1 && maze[x][y] == 1;
}

void Maze::removeWall(int x1, int y1, int x2, int y2)
{
    maze[(x1 + x2) / 2][(y1 + y2) / 2] = 0;
}

bool Maze::saveToFile(const QString &filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filename;
        return false;
    }


    QTextStream out(&file);


    for (const auto &row : maze) {
        for (int cell : row) {
            out << cell << ",";
        }
        out << "\n";
    }

    file.close();
    return true;
}
QVector<QVector<int>>  Maze::getmaze(){
    return maze;
}
// 修改后的 Maze::generateMazeDFSVisual 函数

void Maze::generateMazeDFSVisual(FourWindow* window) {
    if (maze.isEmpty() || maze[0].isEmpty()) return;

    QStack<QPair<int, int>> stack;
    stack.push({startX, startY});
    maze[startX][startY] = 3;

    std::random_device rd;
    std::mt19937 g(rd());



    while (!stack.isEmpty()) {
        int x = stack.top().first;
        int y = stack.top().second;

        QVector<int> directions = {0, 1, 2, 3};
        std::shuffle(directions.begin(), directions.end(), g);

        bool moved = false;
        for (int dir : directions) {
            // 修改点1：增加边界检查
            int nx = x + DX[dir] * 2;
            int ny = y + DY[dir] * 2;

            // 严格校验新坐标的有效性
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 1) {
                int wallX = x + DX[dir];
                int wallY = y + DY[dir];

                // 修改点2：确保墙的位置有效
                if (wallX >= 0 && wallX < rows && wallY >= 0 && wallY < cols) {
                    maze[wallX][wallY] = 0;
                    maze[nx][ny] = 0;

                    // 实时同步数据到绘图模块
                    window->updateMazeData(maze);

                    stack.push({nx, ny});
                    moved = true;

                    window->update();
                    QThread::msleep(50);
                    QApplication::processEvents();
                    break;
                }
            }
        }

        if (!moved) stack.pop();
    }

    // 修改点3：动态设置终点坐标
    if (endX < rows && endY < cols) {
        maze[endX][endY] = 2;
        window->updateMazeData(maze);
        window->update();
    }


}


void Maze::generateMazeprimVisual(FourWindow* window) {
    if (maze.isEmpty() || maze[0].isEmpty()) return;

    // 初始化所有单元格为墙
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            maze[i][j] = 1;

    // 随机选择起始点（可改为参数传入）
    int startX = rows / 2;
    int startY = cols / 2;
    maze[startX][startY] = 3;

    // 候选墙列表（存储格式：墙坐标 + 相邻单元格方向）
    QVector<QVector<int>> walls;

    // 初始化候选墙列表
    auto addWalls = [&](int x, int y) {
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + DX[dir];
            int ny = y + DY[dir];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols)
                walls.append({nx, ny, dir});
        }
    };
    addWalls(startX, startY);

    std::random_device rd;
    std::mt19937 g(rd());

    while (!walls.isEmpty()) {
        // 随机选择一堵墙（Prim算法核心）
        std::shuffle(walls.begin(), walls.end(), g);
        auto wall = walls.takeLast();
        int wx = wall[0], wy = wall[1], dir = wall[2];

        // 计算相邻单元格
        int cx = wx + DX[dir];
        int cy = wy + DY[dir];
        int ox = wx - DX[dir];
        int oy = wy - DY[dir];

        // 边界检查
        if (cx < 0 || cx >= rows || cy < 0 || cy >= cols) continue;
        if (ox < 0 || ox >= rows || oy < 0 || oy >= cols) continue;

        // 打通条件：一边是通道，另一边是墙
        if ((maze[cx][cy] == 1) != (maze[ox][oy] == 1)) {
            maze[wx][wy] = 0; // 打通墙
            int newCell = (maze[cx][cy] == 1) ? cx : ox;
            int newX = (newCell == cx) ? cx : ox;
            int newY = (newCell == cy) ? cy : oy;

            maze[newX][newY] = 0; // 设置新通道
            addWalls(newX, newY); // 添加新墙到候选列表

            // 可视化更新
            window->updateMazeData(maze);
            window->update();
            QThread::msleep(30);
            QApplication::processEvents();
        }
    }

    // 设置终点（动态调整）
    endX = rows - (rows % 2 ? 1 : 2);
    endY = cols - (cols % 2 ? 1 : 2);
    if (endX < rows && endY < cols) {
        maze[endX][endY] = 2;
        window->updateMazeData(maze);
        window->update();
    }
}
void Maze::generateMazebfsVisual(FourWindow* window) {
    if (maze.isEmpty() || maze[0].isEmpty()) return;

    QQueue<QPair<int, int>> queue;
    queue.enqueue({startX, startY});
    maze[startX][startY] = 3;

    std::random_device rd;
    std::mt19937 g(rd());

    while (!queue.isEmpty()) {
        int x = queue.head().first;
        int y = queue.head().second;
        queue.dequeue();

        QVector<int> directions = {0, 1, 2, 3};
        std::shuffle(directions.begin(), directions.end(), g);

        for (int dir : directions) {
            int nx = x + DX[dir] * 2;
            int ny = y + DY[dir] * 2;

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 1) {
                int wallX = x + DX[dir];
                int wallY = y + DY[dir];

                if (wallX >= 0 && wallX < rows && wallY >= 0 && wallY < cols) {
                    maze[wallX][wallY] = 0;
                    maze[nx][ny] = 0;

                    window->updateMazeData(maze);
                    queue.enqueue({nx, ny});

                    window->update();
                    QThread::msleep(30);
                    QApplication::processEvents();
                }
            }
        }
    }

    // 设置终点
    if (endX < rows && endY < cols) {
        maze[endX][endY] = 2;
        window->updateMazeData(maze);
        window->update();
    }
}
bool Maze::loadFromFile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:" << filename;
        return false;
    }

    QTextStream in(&file);
    QString line;
    QVector<QVector<int>> tempMaze;
    int expectedCols = -1;
    bool hasStart = false;
    bool hasEnd = false;

    qDebug() << "正在读取迷宫文件：" << filename;
    qDebug() << "迷宫内容：";

    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList cells = line.split(",", Qt::SkipEmptyParts);
        if (expectedCols == -1) {
            expectedCols = cells.size();
        } else if (cells.size() != expectedCols) {
            qDebug() << "列数不一致，第" << tempMaze.size() + 1 << "行";
            file.close();
            return false;
        }

        QVector<int> row;
        QString rowStr; // 用于打印当前行
        for (const QString &cell : cells) {
            bool ok;
            int value = cell.toInt(&ok);

            if (!ok || value < 0 || value > 3) {
                qDebug() << "无效的单元格值:" << cell;
                file.close();
                return false;
            }

            if (value == 3) {
                if (hasStart) {
                    qDebug() << "存在多个起点";
                    file.close();
                    return false;
                }
                hasStart = true;
            } else if (value == 2) {
                if (hasEnd) {
                    qDebug() << "存在多个终点";
                    file.close();
                    return false;
                }
                hasEnd = true;
            }

            row.append(value);
            rowStr += QString::number(value) + " "; // 将当前单元格添加到行字符串
        }

        tempMaze.append(row);
        qDebug() << rowStr; // 打印当前行
    }

    file.close();

    if (tempMaze.isEmpty()) {
        qDebug() << "迷宫为空";
        return false;
    }
    if (!hasStart) {
        qDebug() << "缺少起点(3)";
        return false;
    }
    if (!hasEnd) {
        qDebug() << "缺少终点(2)";
        return false;
    }

    maze = tempMaze;
    rows = maze.size();
    cols = maze[0].size();

    qDebug() << "迷宫读取成功，行数：" << rows << "，列数：" << cols;
    return true;
}
int Maze::getstartx() const{
    return startX;
}
int Maze::getstarty() const{
    return startY;
}
int Maze::getendx() const{
    return endX;
}
int Maze::getendy() const{
    return endY;
}
int Maze::getRows() const{
    return rows;
}
int Maze::getCols() const{
    return cols;
}
QPair<int, int> Maze::findStartPosition() {
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 3) {
                maze[i][j]=0;
                return qMakePair(i, j);
            }
        }
    }

    return qMakePair(0, 0); // 默认返回 (0,0)，避免未找到的情况
}
QPair<int, int> Maze::findEndPosition() const {
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == 2) {
                return qMakePair(i, j);
            }
        }
    }
    return qMakePair(-1, -1);
}
