#include "missile.h"
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>

Missile::Missile(int startX, int startY, int endX, int endY, bool bon, QGraphicsItem *parent)
    : QObject(), QGraphicsItemGroup(parent)
{
    bonus =bon;
    // Create and add the line
    line = new QGraphicsLineItem(startX, startY, startX, startY, this);
    QPen bluepen(Qt::blue);
    QPen yellowpen(Qt::yellow);

    // Connect timer to move slot
    connect(&timer, &QTimer::timeout, this, &Missile::move);
    timer.start(20); // Adjust timer interval as needed

    // Set up explosion
    explosion = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
    explosion->setPos(endX, endY);

    if(bonus) {
        line->setPen(yellowpen);
        explosion->setBrush(Qt::yellow);
    }
    else {
        line->setPen(bluepen);
        explosion->setBrush(Qt::blue);
    }
}

void Missile::move()
{
    // Move the line's end point towards the explosion's position
    QPointF lineEndPoint = line->line().p2();
    QPointF explosionPos = explosion->pos();
    QPointF direction = explosionPos - lineEndPoint;
    qreal distance = QLineF(lineEndPoint, explosionPos).length();
    qreal step = 5.0;
    if (distance > step) {
        direction *= step / distance;
        lineEndPoint += direction;
        line->setLine(QLineF(line->line().p1(), lineEndPoint));
    } else {
        explode();
    }
}

void Missile::explode()
{
    // Increase explosion size gradually
    qreal scaleFactor = explosion->scale() + 0.1;
    explosion->setScale(scaleFactor);

    int threshold =7;
    if (bonus)
        threshold =10;

    // Remove the missile and explosion when the explosion reaches a certain size
    if (scaleFactor > threshold)
    {
        scene()->removeItem(line); // Remove the line
        scene()->removeItem(explosion); // Remove the explosion
        delete this; // Delete the missile object
    }
}
