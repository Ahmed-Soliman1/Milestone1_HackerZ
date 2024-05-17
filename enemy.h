#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QTimer>

//making the enemy inherit from ellipse item
class Enemy : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

public:
    Enemy(QGraphicsItem* parent = nullptr);
    void move();


private:
    qreal angle;
    qreal speed;
    QTimer* timer;
    QGraphicsEllipseItem* explosion;
    QList<QGraphicsItem*> trailItems;
};

#endif // ENEMY_H
