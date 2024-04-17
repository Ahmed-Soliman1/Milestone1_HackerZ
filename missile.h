#ifndef MISSILE_H
#define MISSILE_H
#include <QGraphicsItem>
#include <QObject>

class Missile: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Missile(int x, int y);
    int xleft;
    int yleft;
    int steps;
    bool bonus;

public slots:
    void move();
    void explode();
};

#endif // MISSILE_H
