#include "enemy.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QtMath>
#include <QMessageBox>

#include "player.h"

Enemy::Enemy(QGraphicsItem *parent) : QObject(), QGraphicsEllipseItem(parent)
{
    // Set up the ellipse
    setRect(0, 0, 10, 10);
    setBrush(Qt::red);

    //randomizing the initial position the enemy is created to be bounded
    qreal startX = QRandomGenerator::global()->bounded(200, 600); // Adjust according to your scene width
    setPos(startX, 0);
    //randomizing the angle the enemy moves with to be bounded
    angle = QRandomGenerator::global()->bounded(-30,30);

    // connecting the timer to the move function so that the enemy keeps moving
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

            scene()->removeItem(this);

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



}


