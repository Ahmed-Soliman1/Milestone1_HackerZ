#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsRectItem>

class Player : public QObject,  public QGraphicsPixmapItem
{Q_OBJECT
public:
    Player();

    void keyPressEvent(QKeyEvent * event);
    static int scoreValue;
    static QGraphicsTextItem* score;
    static int healthValue;
signals:
    void spaceBarPressed(const QPointF& pos);


};

#endif // PLAYER_H
