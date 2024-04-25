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

    //base rectangle
    QGraphicsRectItem *rectangle = new QGraphicsRectItem(92, 560, 612, 40); // Change dimensions as needed
    QPen pen(Qt::green);
    //rectangle->setPen(pen);
    scene.addItem(rectangle);

    // Create bases as rectangles
    QGraphicsRectItem *base1 = new QGraphicsRectItem(132, 570, 20, 20); // Adjust size and position as needed
    QGraphicsRectItem *base2 = new QGraphicsRectItem(380, 570, 20, 20);
    QGraphicsRectItem *base3 = new QGraphicsRectItem(660, 570, 20, 20);
    base1->setBrush(Qt::green); // Set color if needed
    base2->setBrush(Qt::green);
    base3->setBrush(Qt::green);
    scene.addItem(base1);
    scene.addItem(base2);
    scene.addItem(base3);

    // Create the Player
    Player *player = new Player();
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
        srand(time(NULL));
        int randomValue = rand() % 3 + 1;

        if (randomValue==1){
            Missile *missile = new Missile(390, 580, player->pos().x()+13, player->pos().y()+12);
            scene.addItem(missile);
        }
        else if (randomValue==2){
            Missile *missile = new Missile(390, 580, player->pos().x()+13, player->pos().y()+12);
            scene.addItem(missile);
        }
        else{
            Missile *missile = new Missile(390, 580, player->pos().x()+13, player->pos().y()+12);
            scene.addItem(missile);
        }


    });





    // Create a view and set the scene
    QGraphicsView view(&scene);
    view.setWindowTitle("Missile Command");
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setBackgroundBrush(Qt::black);
    view.show();

    // Create a timer for creating enemies
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&scene]() {
        Enemy *enemy = new Enemy();
        scene.addItem(enemy);
    });
    timer.start(2000); // Create enemies every 2 seconds

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




    return a.exec();
}
