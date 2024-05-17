 #include "player.h"
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsScene>

Player::Player(QGraphicsTextItem* scorep,QGraphicsTextItem* healthp) {
    this->score=scorep;
    this->health=healthp;
    numshoots=0;
    // Load player image and set its size
    setPixmap(QPixmap(":/images/cursor.png"));

    setScale(0.5);

}

void Player::keyPressEvent(QKeyEvent *event)
{
    // *******  Event Handling for the Player ********
    if(event->key()== Qt::Key_Left)
    {
        if(x()>4.8)
        {
            setPos(x()-10,y());
        }
    }
    else if(event->key()== Qt::Key_Right)
    { if(x()< 775)
            setPos(x()+10,y());
    }
    else if(event->key()== Qt::Key_Up)
    { if(y()>0)
            setPos(x(),y()-10);
    }
    else if(event->key()== Qt::Key_Down)
    { if(y()<500)
            setPos(x(),y()+10);
    }
    else if(event->key()== Qt::Key_Space)
    {
        // Get the scene position of the player
        QPointF scenePos = mapToScene(0, 0);

        // Calculate the scene position of the player manually
        QPointF spaceBarPos(scenePos.x() + pos().x(), scenePos.y() + pos().y());

        emit spaceBarPressed(spaceBarPos);

    }
}
