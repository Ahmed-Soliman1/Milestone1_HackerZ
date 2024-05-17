 #include "player.h"
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsScene>


Player::Player(QGraphicsTextItem* scorep,QGraphicsTextItem* healthp, QGraphicsTextItem* levelp) {
    this->score=scorep;
    this->health=healthp;
    this->levelLabel=levelp;
    numshoots=0;


    //loading player image and scaling its size
    setPixmap(QPixmap(":/images/cursor.png"));
    setScale(0.5);

}

void Player::keyPressEvent(QKeyEvent *event)
{
    // *******  Event Handling for the Player that checks if it is in boundries ********
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
        //getting the scene position to where the space bar was clicked to be sent as a parameter in the signal Spacebar pressed
        QPointF scenePos = mapToScene(0, 0);
        QPointF spaceBarPos(scenePos.x() + pos().x(), scenePos.y() + pos().y());

        emit spaceBarPressed(spaceBarPos);

    }
}
