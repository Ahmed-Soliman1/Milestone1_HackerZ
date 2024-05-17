#include "game.h"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include <QMessageBox>
#include <QPushButton>
#include <QRandomGenerator>
#include <QApplication>

/*Game::Game(QGraphicsScene* scene, QGraphicsView* view)
    : scene(scene), view(view), level(1), scoreValue(0), healthValue(3), timer(new QTimer(this)) {
    // Initialize base and rectangle
    QPixmap pixmap(":/images/base.png");
    QGraphicsPixmapItem *base = new QGraphicsPixmapItem(pixmap);
    base->setPos(90, 548);
    base->setScale(1.2);
    scene->addItem(base);

    QGraphicsRectItem *rectangle = new QGraphicsRectItem(92, 560, 612, 40);
    scene->addItem(rectangle);

    // Display score
    score = new QGraphicsTextItem;
    score->setFont(QFont("times", 16));
    score->setPlainText("Score: " + QString::number(scoreValue));
    score->setDefaultTextColor(Qt::blue);
    score->setPos(view->width() - 150, 10);
    scene->addItem(score);

    // Display health
    health = new QGraphicsTextItem;
    health->setFont(QFont("times", 16));
    health->setPlainText("Health: " + QString::number(healthValue));
    health->setDefaultTextColor(Qt::blue);
    health->setPos(view->width() - 150, 60);
    scene->addItem(health);

    // Display level
    levelLabel = new QGraphicsTextItem;
    levelLabel->setFont(QFont("times", 16));
    levelLabel->setPlainText("Level: " + QString::number(level));
    levelLabel->setDefaultTextColor(Qt::blue);
    levelLabel->setPos(view->width() - 150, 110);
    scene->addItem(levelLabel);

    connect(timer, &QTimer::timeout, this, &Game::spawnEnemy);
}

void Game::startGame() {
    showStartDialog();
}

void Game::spawnEnemy() {
    Enemy* enemy = new Enemy(level);
    scene->addItem(enemy);

    connect(enemy, &Enemy::enemyDestroyed, this, &Game::handleEnemyDestroyed);
    connect(enemy, &Enemy::reachedBase, this, &Game::handleReachedBase);
}

void Game::handleEnemyDestroyed() {
    scoreValue++;
    score->setPlainText("Score: " + QString::number(scoreValue));

    if (scoreValue == 1 + 5 * level) {
        timer->stop();
        emit levelCompleted();
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
}

void Game::handleReachedBase() {
    healthValue--;
    health->setPlainText("Health: " + QString::number(healthValue));

    if (healthValue == 0) {
        emit gameOver();
        QMessageBox::information(view, "Game Over", "You lost the game!");
        QApplication::quit();
    }
}

void Game::showStartDialog() {
    QMessageBox proceed;
    proceed.setWindowTitle("Play");
    proceed.setText("Do you want to start the game?");
    QPushButton* customButton = proceed.addButton("Start", QMessageBox::AcceptRole);
    proceed.exec();

    if (proceed.clickedButton() == customButton) {
        createPlayer();
        timer->start(4500 - 500 * level); // Start enemy spawn timer
    } else {
        QApplication::quit();
    }
}

int Player::scoreValue = 0;
QGraphicsTextItem* Player::score;
int Player::coins=0;

int Player::healthValue =3;
QGraphicsTextItem* Player::health;
bool Player::bonus;

QGraphicsTextItem* Player::levelLabel;

void Game::createPlayer() {
    player = new Player(score, health);
    player->setPixmap(QPixmap(":/images/cursor.png"));
    player->setScale(0.05);
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(400, 400); // Adjust player position

    connect(player, &Player::spaceBarPressed, [this]() {
        int x;
        if (player->pos().x() < 267)
            x = 133;
        else if (player->pos().x() > 533)
            x = 667;
        else
            x = 390;
        Missile* missile = new Missile(x, 580, player->pos().x() + 13, player->pos().y() + 12, player->bonus);
        scene->addItem(missile);
    });
}

void Game::resetPlayerStats() {
    scoreValue = 0;
    healthValue = 3;
    score->setPlainText("Score: " + QString::number(scoreValue));
    health->setPlainText("Health: " + QString::number(healthValue));
}*/
