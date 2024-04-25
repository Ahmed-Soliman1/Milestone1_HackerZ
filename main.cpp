#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector2D>
#include <QDebug> // Add this for qDebug

#include <QTimer>
#include "player.h"
#include "enemy.h"
#include "missile.h"

#include <cstdlib>
#include <ctime>

// Inside your main() function or at the beginning of your program


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    // Create a scene
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 600); // Set scene boundaries

    //create base
    QPixmap pixmap(":/images/base.png");
    // Adjust size here
    QGraphicsPixmapItem *base = new QGraphicsPixmapItem(pixmap);
    base->setPos(90, 548);
    base->setScale(1.2);
    scene.addItem(base);

    // Create bases as rectangles
    QGraphicsRectItem *base1 = new QGraphicsRectItem(122, 565, 40, 40); // Adjust size and position as needed
    QGraphicsRectItem *base2 = new QGraphicsRectItem(370, 565, 40, 40);
    QGraphicsRectItem *base3 = new QGraphicsRectItem(650, 565, 40, 40);
    base1->setBrush(Qt::green); // Set color if needed
    base2->setBrush(Qt::green);
    base3->setBrush(Qt::green);
    scene.addItem(base1);
    scene.addItem(base2);
    scene.addItem(base3);

    // Create a view and set the scene
    QGraphicsView view(&scene);
    view.setWindowTitle("Missile Command");
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setBackgroundBrush(Qt::black);
    view.show();

    // Displaying the score
    QGraphicsTextItem* score = new QGraphicsTextItem;
    score->setFont(QFont("times",16));
    score->setPlainText("Score: " +QString::number(0));
    score->setDefaultTextColor(Qt::blue);
    score->setPos(view.width()-150, 10);
    scene.addItem(score);

    // Displaying the health
    QGraphicsTextItem* health = new QGraphicsTextItem;
    health->setFont(QFont("times",16));
    health->setPlainText("Health: " +QString::number(3));
    health->setDefaultTextColor(Qt::blue);
    health->setPos(view.width()-150, 60);
    scene.addItem(health);


    // Create the Player
    Player *player = new Player(score,health);
    player->setPixmap(QPixmap(":/images/cursor.png"));
    player->setScale(0.05);
    scene.addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(400, 400); // Adjust player position




    // Connect Player signal to create missile and explosion
    QObject::connect(player, &Player::spaceBarPressed, [&scene, base1, base2, base3, &player](const QPointF& pos) {
        qDebug() << "Space bar pressed!";
        //QPointF FireBase;
        if (player->bonus){
            player->numshoots++;
            if (player->numshoots>3)
            {
                player->numshoots=0;
                player->bonus=false;
            }
        }
        Missile *missile = new Missile(390, 580, player->pos().x()+13, player->pos().y()+12, player->bonus);
        scene.addItem(missile);

    });



    // Create a timer for creating enemies
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&scene]() {
        Enemy *enemy = new Enemy();
        scene.addItem(enemy);
    });
    timer.start(2000); // Create enemies every 2 seconds




    return a.exec();
}
