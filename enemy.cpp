#include "enemy.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QtMath>
#include "missile.h""

Enemy::Enemy(QGraphicsItem *parent) : QObject(), QGraphicsEllipseItem(parent)
{
    // Set up the ellipse
    setRect(0, 0, 10, 10);
    setBrush(Qt::red);

    // Set up initial position and angle
    qreal startX = QRandomGenerator::global()->bounded(200, 800); // Adjust according to your scene width
    setPos(startX, 0);
    angle = QRandomGenerator::global()->bounded(-30,30);

    // Set up speed and timer
    speed = 1; // Adjust as needed
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(20); // Adjust timer interval as needed
}

void Enemy::move()
{
    qreal dx = speed * qSin(qDegreesToRadians(angle));
    qreal dy = speed * qCos(qDegreesToRadians(angle));
    setPos(x() + dx, y() + dy);

    QList<QGraphicsItem*> collisions = collidingItems(Qt::IntersectsItemShape);
    foreach (QGraphicsItem* item, collisions) {
        if (item->type() == QGraphicsEllipseItem::Type) {
            QGraphicsEllipseItem* ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            if (ellipseItem && ellipseItem->brush().color() == Qt::blue) {
                scene()->removeItem(ellipseItem); // Remove the blue ellipse
                scene()->removeItem(this); // Remove the enemy
                delete this;
                return;
            }
        }

    }


    // Draw a red line as a trail
    if (scene()) {
        QPen pen(Qt::red, 2);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        QPainterPath path;
        path.moveTo(x() + 5, y() + 5); // Center of the ellipse
        path.lineTo(x() + dx + 5, y() + dy + 5); // New position
        scene()->addPath(path, pen);
    }

    // If the enemy is out of the scene, remove it
    if (y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}
