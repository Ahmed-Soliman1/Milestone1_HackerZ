#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QTimer>

class Enemy : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

public:
    Enemy(QGraphicsItem* parent = nullptr);
    void move();
    void explode(qreal x, qreal y);

private:
    qreal angle;
    qreal speed;
    QTimer* timer;
    QGraphicsEllipseItem* explosion;
    QList<QGraphicsItem*> trailItems;
};

#endif // ENEMY_H
