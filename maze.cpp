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
    this->startX = qBound(0, startX, rows - 1); // 起点X坐标限制在[0, rows-1]
    this->startY = qBound(0, startY, cols - 1);
    this->endX = qBound(0, endX, rows - 1);
    this->endY = qBound(0, endY, cols - 1);

     // 初始化迷宫
    maze = QVector<QVector<int>>(rows, QVector<int>(cols, 1));

}



// **辅助函数**
bool Maze::isValid(int x, int y)
{
    return x > 0 && x < rows - 1 && y > 0 && y < cols - 1 && maze[x][y] == 1;
}

// 移除两坐标之间的墙壁
void Maze::removeWall(int x1, int y1, int x2, int y2)
{
    maze[(x1 + x2) / 2][(y1 + y2) / 2] = 0;
}

// 将迷宫保存到文件
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


// 使用深度优先搜索（DFS）生成迷宫，并可视化生成过程
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
                    QThread::msleep(50);// 暂停50毫秒
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

// 使用Prim算法生成迷宫，并可视化生成过程
void Maze::generateMazeprimVisual(FourWindow* window) {
    if (maze.isEmpty() || maze[0].isEmpty()) return;

    maze[startX][startY] = 0;

    QVector<QVector<int>> walls; // 存储候选墙壁

    // 初始化候选墙列表
    auto addWalls = [&](int x, int y) {
        for (int dir = 0; dir < 4; ++dir) {
            int wallX = x + DX[dir];
            int wallY = y + DY[dir];
            int cellX = x + DX[dir]*2;
            int cellY = y + DY[dir]*2;

            if (cellX >= 0 && cellX < rows && cellY >= 0 && cellY < cols)
                walls.append({wallX, wallY, dir});// 将墙壁加入候选列表
        }
    };

    addWalls(startX, startY); // 从起点开始添加墙壁

    std::random_device rd;
    std::mt19937 g(rd());

    while (!walls.isEmpty()) {
        // 随机选择一堵墙
        std::shuffle(walls.begin(), walls.end(), g); // 随机打乱墙壁顺序
        auto wall = walls.takeLast();
        int wx = wall[0], wy = wall[1], dir = wall[2];

        // 计算相邻单元格
        int cx = wx + DX[dir];
        int cy = wy + DY[dir];
        int ox = wx - DX[dir];
        int oy = wy - DY[dir];

        // 边界检查
        bool valid1 = (cx >= 0 && cx < rows && cy >= 0 && cy < cols);
        bool valid2 = (ox >= 0 && ox < rows && oy >= 0 && oy < cols);
        if (!valid1 || !valid2) continue;

        // 检查是否一通路一墙
        if ((maze[cx][cy] == 0) ^ (maze[ox][oy] == 0)) {
            // 打通墙
            maze[wx][wy] = 0;

            // 确定新扩展的单元格（修正此处变量错误）
            int newX, newY;
            if (maze[cx][cy] == 1) { // cx, cy是未访问的墙
                newX = cx;
                newY = cy;
            } else { // ox, oy是未访问的墙
                newX = ox;
                newY = oy;
            }

            // 设置新通路
            maze[newX][newY] = 0;
            addWalls(newX, newY);

            // 可视化更新
            window->updateMazeData(maze);
            window->update();
            QThread::msleep(50);
            QApplication::processEvents();
        }
    }

    maze[startX][startY] = 3;
    maze[endX][endY] = 2;
    window->updateMazeData(maze);
    window->update();
}
// 从文件加载迷宫
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

// 查找迷宫中的起点位置
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

// 查找迷宫中的终点位置
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

// 使用Kruskal算法生成迷宫，并可视化生成过程
void Maze::generateMazeKruskalVisual(FourWindow* window) {
    // 初始化全墙
    maze = QVector<QVector<int>>(rows, QVector<int>(cols, 1));

    // 生成所有可能的边（墙）
    QVector<Edge> edges;
    for (int x = 0; x < rows; x += 2) {
        for (int y = 0; y < cols; y += 2) {
            // 向右的墙
            if (y + 2 < cols) {
                edges.append({x, y, x, y+2, x, y+1});
            }
            // 向下的墙
            if (x + 2 < rows) {
                edges.append({x, y, x+2, y, x+1, y});
            }
        }
    }

    // 随机打乱边
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(edges.begin(), edges.end(), g);

    // 并查集初始化
    QVector<int> parent(rows * cols);
    QVector<int> rank(rows * cols, 0);
    for (int i = 0; i < rows*cols; ++i) {
        parent[i] = i;
    }

    // 处理每条边
    for (const Edge& edge : edges) {
        int cell1 = edge.x1 * cols + edge.y1;
        int cell2 = edge.x2 * cols + edge.y2;

        if (findParent(parent, cell1) != findParent(parent, cell2)) {
            // 打破墙壁
            maze[edge.wallX][edge.wallY] = 0;
            maze[edge.x1][edge.y1] = 0;  // 确保单元格是路径
            maze[edge.x2][edge.y2] = 0;

            // 更新可视化
            window->updateMazeData(maze);
            window->update();
            QThread::msleep(50);
            QApplication::processEvents();

            // 合并集合
            unionSets(parent, rank, cell1, cell2);
        }
    }

    // 标记起点和终点
    maze[startX][startY] = 3;
    maze[endX][endY] = 2;
    window->updateMazeData(maze);
    window->update();
}


// 并查集的查找操作
int Maze::findParent(QVector<int>& parent, int cell) {
    if (parent[cell] != cell) {
        parent[cell] = findParent(parent, parent[cell]);
    }
    return parent[cell];
}


// 并查集的合并操作
void Maze::unionSets(QVector<int>& parent, QVector<int>& rank, int x, int y) {
    int rootX = findParent(parent, x);
    int rootY = findParent(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootX] = rootY;
            if (rank[rootX] == rank[rootY]) {
                rank[rootY]++;
            }
        }
    }
}

