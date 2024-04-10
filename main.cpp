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
    view.show();


    // Create a player object and add it to the scene
    Player *player = new Player();
    scene.addItem(player);

    // Set focus to the player object
    player->setFocus();

    return a.exec();
}
