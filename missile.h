// missile.h
#ifndef MISSILE_H
#define MISSILE_H

#include <QObject>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QTimer>

class Missile : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    Missile(int startX, int startY, int endX, int endY, QGraphicsItem *parent = nullptr);

public slots:
    void explode();
    void move();

private:
    QGraphicsLineItem *line;
    QGraphicsEllipseItem *explosion;
    QTimer timer;
};

#endif // MISSILE_H
