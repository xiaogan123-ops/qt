#ifndef ROLE_H
#define ROLE_H

#include <QObject>
#include <QPoint>
#include <QImage>
#include <QPainter>

class Role : public QObject
{
    Q_OBJECT

public:
    explicit Role(QObject *parent = nullptr); // 构造函数

    // 设置角色的初始位置
    void setPosition(int row, int col);

    // 移动角色到指定相对位置
    void Move(int dRow, int dCol);

    // 重置角色位置
    void reset();

    // 绘制角色，动态根据迷宫单元格大小调整显示
    void Paint(QPainter* painter, const QPoint& offset, int cellWidth, int cellHeight);

    // 获取角色当前所在的行和列
    int row() const ;
    int col() const;


    int mrow;              // 当前角色所在行
    int mcol;              // 当前角色所在列
    int startRow;          // 角色起始行（用于重置）
    int startCol;          // 角色起始列（用于重置）
    QImage mImage;         // 角色的图片
};

#endif // ROLE_H
