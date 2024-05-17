#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsRectItem>

class Player : public QObject,  public QGraphicsPixmapItem
{Q_OBJECT
public:

    Player(QGraphicsTextItem* scorep=0, QGraphicsTextItem* healthp=0, QGraphicsTextItem* levelp=0);

    void keyPressEvent(QKeyEvent * event);
    static int scoreValue;
    static QGraphicsTextItem* score;
    static int healthValue;
    static QGraphicsTextItem* health;
    static int coins;
    static bool bonus;
    static int level;
    static QGraphicsTextItem* levelLabel;
    static int numshoots;
signals:
    void spaceBarPressed(const QPointF& pos);


};

#endif // PLAYER_H
