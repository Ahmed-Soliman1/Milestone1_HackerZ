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
int Player::numshoots = 0;

int Player::level = 1;
QGraphicsTextItem* Player::levelLabel;

void Enemy::move()
{
    qreal dx = speed * qSin(qDegreesToRadians(angle));
    qreal dy = speed * qCos(qDegreesToRadians(angle));
    qreal new_x = x() + dx;
    qreal new_y = y() + dy;

    //check if the enemy's new position is out of bounds on the sides
    if (new_x < 0) {
        //checks if the enemy is going out of the left side
        new_x = 0;
        //changing the angle to negative to stimulate bounce
        angle = -angle;
    } else if (new_x > scene()->width() - rect().width()) {
        //checks if the enemy is going out of the right side
        new_x = scene()->width() - rect().width();
        angle = -angle; //changing the angle to negative to stimulate bounce
    }

    // Update the position
    setPos(new_x, new_y);
    //Handling the collisions of enemy
    QList<QGraphicsItem*> collisions = collidingItems(Qt::IntersectsItemShape);
    foreach (QGraphicsItem* item, collisions) {
        if (item->type() == QGraphicsEllipseItem::Type) {
            QGraphicsEllipseItem* ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);//handeling if the enemy collides with ellipse(the explosion of the missile)
            if ((ellipseItem && ellipseItem->brush().color() == Qt::blue)||(ellipseItem && ellipseItem->brush().color() == Qt::yellow)) {

                Player::scoreValue++;
                Player::score->setPlainText("Score: " +QString::number(Player::scoreValue));
                scene()->removeItem(this); //if it collides it is removed from the scene

                if (Player::scoreValue==5*Player::level)
                {
                    if (Player::level < 5) {
                        QMessageBox win;
                        win.setWindowTitle("You won");
                        win.setText("You finished level " + QString::number(Player::level) + ". You can now proceed to the next level.");
                        QPushButton* next = win.addButton("Go to next level", QMessageBox::AcceptRole);
                        QPushButton* quit = win.addButton("Quit", QMessageBox::AcceptRole);
                        win.setDefaultButton(next);
                        win.exec();

                        if (win.clickedButton() == next) {  //proceeding to next level
                            Player::level++;
                            Player::levelLabel->setPlainText("Level: " + QString::number(Player::level));
                            Player::scoreValue = 0;
                            Player::healthValue = 3;
                            Player::score->setPlainText("Score: " + QString::number(0));
                            Player::health->setPlainText("Health: " + QString::number(3));
                        }
                        else if (win.clickedButton() == quit)
                            exit(0);
                    }
                    else {  // In case of finishing all levels
                        QMessageBox congrat;
                        congrat.setWindowTitle("Well Done");
                        congrat.setText("Congratulations! You finished all the levels!");
                        congrat.exec();
                        exit(0);
                    }
                }
                else if (Player::scoreValue % 5 == 0) { // enabling bonus weapon
                    Player::coins += 100;
                    QMessageBox weapon;
                    weapon.setWindowTitle("Buy Weapon");
                    weapon.setText("Your coins are now: " + QString::number(Player::coins) + ". Do you want to use 100 coins to buy a weapon?");
                    weapon.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                    weapon.setDefaultButton(QMessageBox::Yes);                   
                    if (weapon.exec() == QMessageBox::Yes) {
                        Player::numshoots += 3* Player::coins/100;   // adding the number of bonus shoots he'll get
                        Player::coins = 0;
                        Player::bonus=true;
                    }
                }

                delete this;
                return;
            }
        }

        else if (typeid(*(item))==typeid(QGraphicsRectItem)) {  // collision with base
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
