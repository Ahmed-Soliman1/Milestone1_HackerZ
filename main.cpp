#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector2D>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include <QPushButton>
#include <QTimer>>

\


QTimer* timer = nullptr;

void createTimerForEnemies(QGraphicsScene &scene, Player *player) {
    // Delete the old timer if it exists
    if (timer != nullptr) {
        timer->stop();
        delete timer;
    }



    // Create a new timer with the updated interval
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&scene, &player]() {
        Enemy* enemy = new Enemy(player->level);
        scene.addItem(enemy);
    });
    timer->start(4500 - 500 * player->level); // Creates enemies at an interval
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create a scene
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 600); // Set scene boundaries

    // Create base
    QPixmap pixmap(":/images/base.png");
    QGraphicsPixmapItem *base = new QGraphicsPixmapItem(pixmap);
    base->setPos(90, 548);
    base->setScale(1.2);
    scene.addItem(base);

    // Create rectangle approximately the same size as the base
    QGraphicsRectItem *rectangle = new QGraphicsRectItem(92, 560, 612, 40);
    scene.addItem(rectangle);

    // Creating a view and set the scene
    QGraphicsView view(&scene);
    view.setWindowTitle("Missile Command");
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setBackgroundBrush(Qt::black);
    view.show();

    // Displaying the score
    QGraphicsTextItem* score = new QGraphicsTextItem;
    score->setFont(QFont("times", 16));
    score->setPlainText("Score: " + QString::number(0));
    score->setDefaultTextColor(Qt::blue);
    score->setPos(view.width() - 150, 10);
    scene.addItem(score);

    // Displaying the health
    QGraphicsTextItem* health = new QGraphicsTextItem;
    health->setFont(QFont("times", 16));
    health->setPlainText("Health: " + QString::number(3));
    health->setDefaultTextColor(Qt::blue);
    health->setPos(view.width() - 150, 60);
    scene.addItem(health);

    // Displaying the level
    //    int level = 1;
    QGraphicsTextItem* levelLabel = new QGraphicsTextItem;
    levelLabel->setFont(QFont("times", 16));
    levelLabel->setPlainText("Level: " + QString::number(1));
    levelLabel->setDefaultTextColor(Qt::blue);
    levelLabel->setPos(view.width() - 150, 110);
    scene.addItem(levelLabel);

    QMessageBox proceed;
    proceed.setWindowTitle("Play");
    proceed.setText("Do you want to start the game?");
    QPushButton* customButton = proceed.addButton("Start", QMessageBox::AcceptRole);
    proceed.exec();

    if (proceed.clickedButton() == customButton) {
        // Creating the Player
        Player* player = new Player(score, health, levelLabel);
        player->setPixmap(QPixmap(":/images/cursor.png"));
        player->setScale(0.05);
        scene.addItem(player);
        player->setFlag(QGraphicsItem::ItemIsFocusable);
        // Setting focus to player to be controlled
        player->setFocus();
        player->setPos(400, 400); // Adjust player position
        int level=1;

        // Connect Player signal to create missile and explosion
        QObject::connect(player, &Player::spaceBarPressed, [&scene, player]() {
            if (player->bonus) {
                player->numshoots++;
                if (player->numshoots > 3) {
                    player->numshoots = 0;
                    player->bonus = false;
                }
            }
            int x;
            if (player->pos().x() < 267)
                x = 133;
            else if (player->pos().x() > 533)
                x = 667;
            else
                x = 390;
            Missile* missile = new Missile(x, 580, player->pos().x() + 13, player->pos().y() + 12, player->bonus, player->level);
            scene.addItem(missile);
        });
        /*
        // A timer for creating enemies
        QTimer* timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [&scene, &player]() {
            Enemy* enemy = new Enemy(player->level);
            scene.addItem(enemy);
        });
        timer->start(4500 - 0.5 * player->level); // Creates enemies at an interval*/

        createTimerForEnemies(scene, player);
        QTimer* levelCheckTimer = new QTimer();
        QObject::connect(levelCheckTimer, &QTimer::timeout, [&scene, &level, &player]() {
            if (Player::level != level) {

                level = Player::level;

                createTimerForEnemies(scene, player);
            }
        });
        levelCheckTimer->start(2000); // Check for level change every 2 seconds
    }

    return a.exec();
}





















