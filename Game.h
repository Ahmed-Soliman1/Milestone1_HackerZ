#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsTextItem>
/*
class Player;
class Enemy;

class Game : public QObject {
    Q_OBJECT
public:
    Game(QGraphicsScene* scene, QGraphicsView* view);

    void startGame();

signals:
    void gameOver();
    void levelCompleted();

private slots:
    void spawnEnemy();
    void handleEnemyDestroyed();
    void handleReachedBase();

private:
    void showStartDialog();
    void createPlayer();
    void resetPlayerStats();

    QGraphicsScene* scene;
    QGraphicsView* view;
    Player* player;
    QGraphicsTextItem* score;
    QGraphicsTextItem* health;
    QGraphicsTextItem* levelLabel;
    int level;
    int scoreValue;
    int healthValue;
    QTimer* timer;
};
*/
#endif // GAME_H
