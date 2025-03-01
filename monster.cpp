#include "monster.h"
#include <QPropertyAnimation>
#include <QPoint>
#include <QAbstractAnimation>

Monster::Monster(QObject *parent)
    : QObject(parent), mrow(0), mcol(0), routeIndex(0),direction(1)
{
}

void Monster::setPosition(int row, int col)
{
    mrow = row;
    mcol = col;
}

int Monster::row() const { return mrow; }
int Monster::col() const { return mcol; }

void Monster::setPatrolRoute(const QVector<QPair<int, int>> &route) {
    patrolRoute.clear();
    if(route.size() < 2) return;

    // 生成路径点之间的所有中间点
    for(int i=0; i<route.size()-1; ++i){
        auto start = route[i];
        auto end = route[i+1];

        // 水平移动
        if(start.first == end.first){
            int step = (start.second < end.second) ? 1 : -1;
            for(int y=start.second; y!=end.second; y+=step){
                patrolRoute.append(qMakePair(start.first, y));
            }
        }
        // 垂直移动
        else if(start.second == end.second){
            int step = (start.first < end.first) ? 1 : -1;
            for(int x=start.first; x!=end.first; x+=step){
                patrolRoute.append(qMakePair(x, start.second));
            }
        }
    }
    patrolRoute.append(route.last());

    if(!patrolRoute.isEmpty()){
        mrow = patrolRoute[0].first; // 使用第一个路径点的行
        mcol = patrolRoute[0].second; // 使用第一个路径点的列
    }
    routeIndex = 0;
    direction = 1;
}

void Monster::move() {
    if(patrolRoute.size() < 2) return;

    int next = routeIndex + direction;
    if(next >= patrolRoute.size() || next < 0){
        direction *= -1;
        next = routeIndex + direction;
    }

    if(next >=0 && next < patrolRoute.size()){
        routeIndex = next;
        mrow = patrolRoute[routeIndex].first;
        mcol = patrolRoute[routeIndex].second;
    }
}
