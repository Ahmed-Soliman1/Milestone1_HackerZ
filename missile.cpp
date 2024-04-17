#include "missile.h"
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include "player.h"
#include <QBrush>

QBrush yellowBrush(Qt::yellow);
QBrush blueBrush(Qt::blue);
QBrush redBrush(Qt::red);

Missile::Missile(int x,int y, bool bon): QObject(), QGraphicsEllipseItem() {
    bonus =bon;
    if(bonus)
    {
        setRect(0,0,75,75);
        steps=pow(xleft*xleft+yleft*yleft,0.5)/20;
        setBrush(redBrush);
    }
    else
    {
        setRect(0,0,50,50);
        steps=pow(xleft*xleft+yleft*yleft,0.5)/10;
        setBrush(redBrush);
    }

    if (x>scene()->width()/3) {
        setPos(scene()->width()/6,75);
    }
    else if (x<scene()->width()*(2/3)) {
        setPos(scene()->width()/2,75);
    }
    else {
        setPos(scene()->width()*(5/6),75);
    }

    xleft=x-pos().x();
    yleft=y-pos().y();

    steps=pow(xleft*xleft+yleft*yleft,0.5)/10;

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT (move()));
    timer->start(50);
}

void Missile:: move() {
    if (pos().y()>yleft+75)
    {
        setPos(x()+xleft/steps,y()+yleft/steps);

    }
    else
        explode();
}

int Player::scoreValue = 0;
QGraphicsTextItem* Player::score;

void Missile:: explode() {
    scene()->removeItem(this);
    delete this;

    QGraphicsEllipseItem* effect =new QGraphicsEllipseItem;
    if(bonus)
    {
        effect->setRect(pos().x(), pos().y(), 150, 150);
        effect->setBrush(redBrush);
    }
    else
    {
        effect->setRect(pos().x(), pos().y(), 100, 100);
        effect->setBrush(yellowBrush);
    }

    scene()->addItem(effect);
    QList <QGraphicsItem *> missile_colliding_items= effect->collidingItems();
    for(int i=0; i<missile_colliding_items.size(); i++)
    {
        if(typeid(*(missile_colliding_items[i]))==typeid(Enemy))
        {
            Player::scoreValue++;
            Player::score->setPlainText("Score: " +QString::number(Player::scoreValue));
            QGraphicsEllipseItem* enemy_effect =new QGraphicsEllipseItem;
            enemy_effect->setRect(missile_colliding_items[i]->pos().x(), missile_colliding_items[i]->pos().y(), 100, 100);
            enemy_effect->setBrush(blueBrush);
            scene()->addItem(enemy_effect);
            QList <QGraphicsItem *> enemy_colliding_items= effect->collidingItems();
            scene()->removeItem(missile_colliding_items[i]);
            delete missile_colliding_items[i];
            for(int i=0; i<missile_colliding_items.size(); i++)
            {
                while (typeid(*(enemy_colliding_items[i]))==typeid(Enemy))
                {
                    Player::scoreValue++;
                    Player::score->setPlainText("Score: " +QString::number(Player::scoreValue));
                    scene()->removeItem(enemy_colliding_items[i]);
                    delete enemy_colliding_items[i];
                    scene()->removeItem(enemy_effect);
                    delete enemy_effect;
                    QGraphicsEllipseItem* enemy_effect =new QGraphicsEllipseItem;
                    enemy_effect->setRect(missile_colliding_items[i]->pos().x(), missile_colliding_items[i]->pos().y(), 100, 100);
                    enemy_effect->setBrush(blueBrush);
                    scene()->addItem(enemy_effect);
                    enemy_colliding_items= effect->collidingItems();
                }
            }
            scene()->removeItem(enemy_effect);
            delete enemy_effect;
        }
    }
    scene()->removeItem(effect);
    delete effect;
}
