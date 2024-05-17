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
    Enemy(int level, QGraphicsItem* parent = nullptr);
    void move();
    //void explode(qreal x, qreal y);

private:
    //creating private data members to for the enemy
    qreal angle;
    qreal speed;
    QTimer* timer;
    QGraphicsEllipseItem* explosion;
    QList<QGraphicsItem*> trailItems;

};

#endif // ENEMY_H
