#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QVector>
#include <QPair>

class Monster : public QObject
{
    Q_OBJECT
public:
    explicit Monster(QObject *parent = nullptr);

    // 设置初始位置
    void setPosition(int row, int col);
    int row() const;
    int col() const;

    // 设置巡逻路线（路线内各个点将循环移动）
    void setPatrolRoute(const QVector<QPair<int,int>> &route);

    // 每次调用后，怪物移动到巡逻路径上的下一个点
    void move();
     bool patrolRouteEmpty() const { return patrolRoute.isEmpty(); }


signals:
    // 可选：当怪物与角色碰撞时发出信号
    void collided();

private:
    int mrow, mcol;  // 当前所在行列
    QVector<QPair<int,int>> patrolRoute; // 巡逻路径
    int routeIndex;  // 当前在巡逻路径中的索引
     int direction; // 移动方向（1前进，-1后退）
};

#endif // MONSTER_H
