#include "paddle.h"
#include <cmath>
#include <QPainter>

Paddle::Paddle(double x, double y, double w, double h, double vx, double vy,
               QGraphicsItem *parent):
    Entity(x, y, w, h, vx, vy, parent)
{}

void Paddle::moveLeft()
{
    if(left() >= Arkanoid::FIELD_LEFT + fabs(vx()))
    {
        setVx(-fabs(vx()));
        Entity::move();
    }
}

void Paddle::moveRight()
{
    if(right() <= Arkanoid::FIELD_RIGHT - fabs(vx()))
    {
        setVx(+fabs(vx()));
        Entity::move();
    }
}

void Paddle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect());
    painter->setBrush(Qt::NoBrush);
}

bool Paddle::isMoving() const
{
    return m_isMoving;
}

void Paddle::setIsMoving(bool isMoving)
{
    m_isMoving = isMoving;
}
