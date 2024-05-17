#include "missile.h"
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>

Missile::Missile(int startX, int startY, int endX, int endY, bool bon, int level, QGraphicsItem *parent)
    : QObject(), QGraphicsItemGroup(parent)
{
    bonus =bon;
    //Creating a line item
    line = new QGraphicsLineItem(startX, startY, startX, startY, this);
    //creating pen color fror the missiles
    QPen bluepen(Qt::blue);
    QPen yellowpen(Qt::yellow);

    //connect the move function to a timer to move
    connect(&timer, &QTimer::timeout, this, &Missile::move);
    timer.start(10+10*(5-level)); // Adjust timer interval as needed

    //creating the ellipse and setting its position to dummy place  explosion
    explosion = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
    //setting its position to where the the mouse was clicked
    explosion->setPos(endX, endY);

    //if the explosion is bonus use the yellow pen to draw the explosion(ellipse) and the line
    if(bonus) {
        line->setPen(yellowpen);
        explosion->setBrush(Qt::yellow);
    }
    //else set the pen to the blue pen
    else {
        line->setPen(bluepen);
        explosion->setBrush(Qt::blue);
    }
}

void Missile::move()
{
    //moving the the lines endpoint to be at the explosion's position
    QPointF lineEndPoint = line->line().p2();
    QPointF explosionPos = explosion->pos();
    QPointF direction = explosionPos - lineEndPoint;
    qreal distance = QLineF(lineEndPoint, explosionPos).length();
    qreal step = 10;
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
    //Gradually incease the explosion size
    qreal scaleFactor = explosion->scale() + 0.1;
    explosion->setScale(scaleFactor);
    //setting of all explosions to the smaller threshold
    int threshold =7;
    //if the explosion is bonus the threshold vale is changed from 7 to 10
    if (bonus)
        threshold =10;

    //if the ellipse reaches a certain size it is deleted and its trail is deleted
    if (scaleFactor > threshold)
    {
        scene()->removeItem(line); //remoing the line from the scene
        scene()->removeItem(explosion); //remove the explosion from the scene
        delete this; //delete the missile object as a whole from memory
    }
}
