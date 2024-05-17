#include "enemy.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QtMath>
#include <QMessageBox>

#include "player.h"
#include <QPushButton>

Enemy::Enemy(int level, QGraphicsItem *parent) : QObject(), QGraphicsEllipseItem(parent)
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
    timer->start(40-5*level); // Adjust timer interval as needed
}

int Player::scoreValue = 0;
QGraphicsTextItem* Player::score;
int Player::coins=0;

int Player::healthValue =3;
QGraphicsTextItem* Player::health;
bool Player::bonus;

int Player::level = 1;
QGraphicsTextItem* Player::levelLabel;

void Enemy::move()
{
    qreal dx = speed * qSin(qDegreesToRadians(angle));
    qreal dy = speed * qCos(qDegreesToRadians(angle));
    qreal new_x = x() + dx;
    qreal new_y = y() + dy;

    // Check if the new position is out of bounds on the sides
    if (new_x < 0) {
        // Enemy is going out of the left side, adjust its position and angle
        new_x = 0;
        angle = -angle; // Reflect the angle to simulate bounce
    } else if (new_x > scene()->width() - rect().width()) {
        // Enemy is going out of the right side, adjust its position and angle
        new_x = scene()->width() - rect().width();
        angle = -angle; // Reflect the angle to simulate bounce
    }

    // Update the position
    setPos(new_x, new_y);

    QList<QGraphicsItem*> collisions = collidingItems(Qt::IntersectsItemShape);
    foreach (QGraphicsItem* item, collisions) {
        if (item->type() == QGraphicsEllipseItem::Type) {
            QGraphicsEllipseItem* ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            if ((ellipseItem && ellipseItem->brush().color() == Qt::blue)||(ellipseItem && ellipseItem->brush().color() == Qt::yellow)) {

                Player::scoreValue++;
                Player::score->setPlainText("Score: " +QString::number(Player::scoreValue));
                //scene()->removeItem(ellipseItem); // Remove the blue ellipse
                scene()->removeItem(this); // Remove the enemy
                if (Player::scoreValue==/*10+*/5*Player::level)
                {
                    if (Player::level < 5) {
                        QMessageBox win;
                        win.setWindowTitle("You won");
                        win.setText("You finished level " + QString::number(Player::level) + ". You can now proceed to the next level.");
                        QPushButton* newbut = win.addButton("Go to next level", QMessageBox::AcceptRole);
                        win.exec();

                        if (win.clickedButton() == newbut) {
                            Player::level++;
                            Player::levelLabel->setPlainText("Level: " + QString::number(Player::level));
                            Player::scoreValue = 0;
                            Player::healthValue = 3;
                            Player::score->setPlainText("Score: " + QString::number(0));
                            Player::health->setPlainText("Health: " + QString::number(3));
                        }
                    } else {
                        QMessageBox congrat;
                        congrat.setWindowTitle("Well Done");
                        congrat.setText("Congratulations! You finished all the levels!");
                        congrat.exec();
                        exit(0);
                    }
                }
                else if (Player::scoreValue % 5 == 0) {
                    Player::coins += 100;
                    QMessageBox weapon;
                    weapon.setWindowTitle("Buy Weapon");
                    weapon.setText("Your coins are now: " + QString::number(Player::coins) + ". Do you want to use 100 coins to buy a weapon?");
                    weapon.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                    weapon.setDefaultButton(QMessageBox::Yes);
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
