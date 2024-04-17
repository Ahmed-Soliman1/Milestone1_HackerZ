#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create a scene
    QGraphicsScene scene;
    scene.setSceneRect(-200, -200, 400, 400); // Set scene boundaries

    // Create a view and set the scene
    QGraphicsView view(&scene);
    view.setWindowTitle("Player Example");
    view.resize(400, 400);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.show();

    // Displaying the score
    QGraphicsTextItem* score =new QGraphicsTextItem;
    score->setFont(QFont("times",16));
    score->setPlainText("Score: " +QString::number(0));
    score->setDefaultTextColor(Qt::blue);
    score->setPos(view.width()-150,10);
    scene.addItem(score);

    // Displaying the health
    QGraphicsTextItem* health =new QGraphicsTextItem;
    health->setFont(QFont("times",16));
    health->setPlainText("Health: " +QString::number(3));
    health->setDefaultTextColor(Qt::blue);
    health->setPos(view.width()-150,60);
    scene.addItem(health);

    // Create a player object and add it to the scene
    Player *player = new Player();
    scene.addItem(player);

    // Set focus to the player object
    player->setFocus();

    return a.exec();
}
