#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsRectItem>

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Player(QGraphicsItem *parent = nullptr);

    static int scoreValue;
    static QGraphicsTextItem* score;
    static int healthValue;
    static QGraphicsTextItem* health;

signals:
    void leftClicked();

private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // PLAYER_H
