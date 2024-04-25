// missile.cpp
#include "missile.h"
#include <QGraphicsScene>>
#include <QPen>
#include <QBrush>

Missile::Missile(int startX, int startY, int endX, int endY, QGraphicsItem *parent)
    : QObject(), QGraphicsItemGroup(parent)
{
    // Create and add the line
    line = new QGraphicsLineItem(startX, startY, startX, startY, this);
    QPen pen(Qt::blue);
    line->setPen(pen);

    // Connect timer to move slot
    connect(&timer, &QTimer::timeout, this, &Missile::move);
    timer.start(20); // Adjust timer interval as needed

    // Set up explosion
    explosion = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
    explosion->setPos(endX, endY);
    explosion->setBrush(Qt::blue);
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

    // Remove the missile and explosion when the explosion reaches a certain size
    if (scaleFactor > 7.0)
    {
        scene()->removeItem(line); // Remove the line
        scene()->removeItem(explosion); // Remove the explosion
        delete this; // Delete the missile object
    }
}
