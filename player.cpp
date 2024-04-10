#include "player.h"
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

Player::Player(QGraphicsItem *parent) : QObject(), QGraphicsRectItem(parent)
{
    setRect(-200, -200, 400, 400); // Size of the rectangle
    setFlag(QGraphicsItem::ItemIsFocusable);
    setAcceptHoverEvents(true);

    // Create a cursor with the desired shape
    QCursor cursor(Qt::CrossCursor);

    // Set the cursor for the player object
    setCursor(cursor);
}

void Player::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit leftClicked();
    }

    QGraphicsRectItem::mousePressEvent(event);
}

