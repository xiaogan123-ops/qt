#include "role.h"

Role::Role(QObject *parent)
    : QObject(parent)
    , mrow(0)
    , mcol(0)
    , startRow(0)
    , startCol(0)
    , mImage("://res/start0.jpg") // 初始化角色图片
{
    if (mImage.isNull()) {
        qWarning("Failed to load role image!");
    }
}

// 设置角色的初始位置
void Role::setPosition(int row, int col) {
    mrow = row;
    mcol = col;
    startRow = row;
    startCol = col;
}

// 移动角色
void Role::Move(int dRow, int dCol)
{
    mrow += dRow;
    mcol += dCol;
}
int Role::row() const {
    return mrow;
}
int Role::col() const {
    return mcol;
}

// 重置角色位置到初始位置
void Role::reset()
{
    mrow = startRow;
    mcol = startCol;
}

// 绘制角色
void Role::Paint(QPainter* painter, const QPoint& offset, int cellWidth, int cellHeight)
{
    if (mImage.isNull()) {
        return; // 如果角色图片加载失败，直接退出
    }

    // 根据角色当前位置计算绘制坐标
    int x = mcol * cellWidth + offset.x();
    int y = mrow * cellHeight + offset.y();


    QPixmap pixmap = QPixmap::fromImage(mImage);

    // 缩放图片到单元格大小
    QPixmap scaled = pixmap.scaled(cellWidth, cellHeight, Qt::IgnoreAspectRatio);

    // 绘制缩放后的图片
    painter->drawPixmap(x, y, scaled);
}
