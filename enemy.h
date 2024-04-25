#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QPainterPath>
#include <QPen>
#include <QList>
#include "missile.h"

class Enemy : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Enemy(QGraphicsItem *parent = nullptr);

public slots:
    void move();

private:
    QTimer *timer;
    qreal angle;
    qreal speed;
};

#endif // ENEMY_H
