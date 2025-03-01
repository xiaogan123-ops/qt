#include "gameman.h"
#include <QDebug>
#include <QQueue>
#include<QStack>
#include <QRandomGenerator>
#include <QFile>      // 用于文件操作
#include <QIODevice>  // 用于文件 I/O 操作
#include <QTextStream> // 用于文本流操作
#include <QThread>
#include<QPainter>
#include <QRandomGenerator>
Gameman::Gameman(QObject *parent)
    : QObject{parent}, mrow(0), mcol(0) {


}

Gameman::~Gameman() {
    clear();
}

void Gameman::paint(QPainter* _p, QPoint _pos) {
    if (!_p || !_p->isActive()) {
        qDebug() << "无效的 QPainter 对象，无法绘制！";
        return;
    }

    if (mpArr.isEmpty()) {
        qDebug() << "mpArr 为空，无法绘制迷宫！";
        return;
    }


    int cellWidth = 600 / mcol;
    int cellHeight = 600 / mrow;

    for (int i = 0; i < mrow; i++) {
        for (int j = 0; j < mcol; j++) {
            QString img;
            switch (mpArr[i][j]) {
            case 0: img = "://res/ground.jpg"; break;
            case 1: img = "://res/WALL.png"; break;
            case 2: img = "://res/destination.jpg"; break;
            case 3: img = "://res/start0.jpg"; break;
            default: continue;
            }

            QImage image(img);
            if (!image.isNull()) {
                _p->drawImage(QRect(
                                  _pos.x() + j * cellWidth,
                                  _pos.y() + i * cellHeight,
                                  cellWidth, cellHeight
                                  ), image);
            } else {
                qDebug() << "Failed to load image:" << img;
            }
        }
    }

}
// 初始化迷宫
bool Gameman::InitByData(const QVector<QVector<int>>& data) {
    clear(); // 清除旧数据

    if (data.isEmpty()) {
        qDebug() << "迷宫数据为空，加载失败！";
        return false;
    }

    mrow = data.size();
    mcol = data[0].size();

    // 检查所有行列是否一致
    for (const auto &row : data) {
        if (row.size() != mcol) {
            qDebug() << "迷宫数据格式错误，每行列数不一致！";
            return false;
        }
    }
    for (int i = 0; i < mrow; ++i) {
        for (int j = 0; j < mcol; ++j) {
            if (data[i][j] == 2) {
                endX = i;
                endY = j;
            }
        }
    }

    // 如果没有找到终点，设置默认值
    if (endX == -1 || endY == -1) {
        endX = mrow - 1;
        endY = mcol - 1;
    }

    // 直接赋值，避免手动 new/delete
    mpArr = data;

    return true;
}

//检查是否为墙壁
bool Gameman::isWall(int row, int col) const {
    return row < 0 || row >= mrow || col < 0 || col >= mcol || mpArr[row][col] == 1;
}

//获取单元格值
int Gameman::getCell(int row, int col) const {
    if (row >= 0 && row < mrow && col >= 0 && col < mcol) {
        return mpArr[row][col];
    }
    return -1; // 返回 -1 表示无效
}

//设置单元格值
void Gameman::setCell(int row, int col, int value) {
    if (row >= 0 && row < mrow && col >= 0 && col < mcol) {
        mpArr[row][col] = value;
    }
}


void Gameman::clear() {
    mpArr.clear();
    mrow = 0;
    mcol = 0;
}
bool Gameman::isValid(int row, int col) const {
    return (row >= 0) && (row < mpArr.size()) &&
           (col >= 0) && (col <mpArr[0].size());
}

bool Gameman::isRoad(int row, int col) const {
    return isValid(row, col) && (mpArr[row][col] != 1); // 假设 不是1 表示可行走道路
}
