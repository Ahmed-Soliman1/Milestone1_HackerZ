#include "enemy.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QtMath>
#include <QMessageBox>
#include "missile.h"
#include "player.h"

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

int Player::scoreValue = 0;
QGraphicsTextItem* Player::score;
int Player::coins=0;

int Player::healthValue =3;
QGraphicsTextItem* Player::health;
bool Player::bonus;

void Enemy::explode(qreal x, qreal y)
{
    // Create the explosion at the given position (x, y)
    explosion = new QGraphicsEllipseItem(x, y, 1, 1); // Initial size 1x1
    explosion->setBrush(Qt::yellow); // Initial color

    // Increase explosion size gradually
    qreal scaleFactor = explosion->rect().width() + 0.1; // Assuming explosion is a square
    explosion->setRect(x - scaleFactor / 2, y - scaleFactor / 2, scaleFactor, scaleFactor);

    // Remove the explosion when the explosion reaches a certain size
    if (scaleFactor > 7.0)
    {
        foreach (QGraphicsItem* trail, trailItems) {
            scene()->removeItem(trail); // Remove the trail items
            delete trail;
        }
        scene()->removeItem(explosion); // Remove the explosion
        delete explosion; // Delete the explosion object
    }
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
            if ((ellipseItem && ellipseItem->brush().color() == Qt::blue)||(ellipseItem && ellipseItem->brush().color() == Qt::yellow)) {

                Player::scoreValue++;
                Player::score->setPlainText("Score: " +QString::number(Player::scoreValue));
                //scene()->removeItem(ellipseItem); // Remove the blue ellipse
                scene()->removeItem(this); // Remove the enemy
                if (Player::scoreValue % 5 == 0) {
                    Player::coins += 100;
                    QMessageBox weapon;
                    weapon.setWindowTitle("Buy Weapon");
                    weapon.setText("Your coins are now: " + QString::number(Player::coins) + ". Do you want to use 100 coins to buy a weapon?");
                    weapon.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                    weapon.setDefaultButton(QMessageBox::No);
                    if (weapon.exec() == QMessageBox::Yes) {
                        Player::coins -= 100;
                        Player::bonus=true;
                    }
                }

                delete this;
                return;
            }
        }

        else if (typeid(*(item))==typeid(QGraphicsRectItem)) {
            Player::healthValue--;
            Player::health->setPlainText("Health: " +QString::number(Player::healthValue));
            scene()->removeItem(item);
            delete item;
            scene()->removeItem(this); // Remove the enemy
            explode(x(), y());
            if (Player::healthValue==0)
            {
                QMessageBox* over =new QMessageBox;
                over->setText("Game over, your score is: " +QString::number(Player::scoreValue));
                over->exec();

                exit(0);
            }

            delete this;
            return;
        }
    }


    // If the enemy is out of the scene, remove it along with its trail
    if (y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}


