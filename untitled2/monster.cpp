#include "monster.h"
#include <QPropertyAnimation>
#include <QPoint>
#include <QAbstractAnimation>

Monster::Monster(QObject *parent)
    : QObject(parent), mrow(0), mcol(0), routeIndex(0)
{
}

void Monster::setPosition(int row, int col)
{
    mrow = row;
    mcol = col;
}

int Monster::row() const { return mrow; }
int Monster::col() const { return mcol; }

void Monster::setPatrolRoute(const QVector<QPair<int, int>> &route)
{
    patrolRoute.clear();
    if (route.size() < 2) return;

    // 自动生成路径上的所有中间点
    for (int i = 0; i < route.size() - 1; ++i) {
        QPair<int, int> start = route[i];
        QPair<int, int> end = route[i+1];

        // 水平移动
        if (start.first == end.first) {
            int step = (start.second < end.second) ? 1 : -1;
            for (int y = start.second; y != end.second; y += step) {
                patrolRoute.append(qMakePair(start.first, y));
            }
        }
        // 垂直移动
        else if (start.second == end.second) {
            int step = (start.first < end.first) ? 1 : -1;
            for (int x = start.first; x != end.first; x += step) {
                patrolRoute.append(qMakePair(x, start.second));
            }
        }
    }
    patrolRoute.append(route.last()); // 添加最后一个点

    routeIndex = 0;
    direction = 1; // 新增成员变量
    if (!patrolRoute.isEmpty()) {
        mrow = patrolRoute[0].first;
        mcol = patrolRoute[0].second;
    }
}
void Monster::move()
{
    if (patrolRoute.size() < 2) return;

    int nextIndex = routeIndex + direction;

    // 到达端点时反转方向
    if (nextIndex >= patrolRoute.size() || nextIndex < 0) {
        direction *= -1; // 反转方向
        nextIndex = routeIndex + direction; // 更新下一步索引
    }

    // 确保索引有效
    if (nextIndex < 0 || nextIndex >= patrolRoute.size()) {
        return; // 处理异常情况
    }

    // 更新位置
    routeIndex = nextIndex;
    mrow = patrolRoute[routeIndex].first;
    mcol = patrolRoute[routeIndex].second;
}
