#include "ball.h"
#include <QPainter>

Ball::Ball(double x, double y, double r, double vx, double vy, QGraphicsItem *parent):
    Entity(x, y, 2 * r, 2 * r, vx, vy, parent)
{}

void Ball::move()
{
    Entity::move();
    if(left() <= Arkanoid::FIELD_LEFT || right() >= Arkanoid::FIELD_RIGHT)
    {
        setVx(-vx());
    }
    if(top() <= Arkanoid::FIELD_TOP || bottom() >= Arkanoid::FIELD_BOTTOM)
    {
        setVy(-vy());
    }
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect());
    painter->setBrush(Qt::NoBrush);
}

