#include "entity.h"

Entity::Entity(double x, double y, double w, double h, double vx, double vy,
               QGraphicsItem *parent):
    QGraphicsItem(parent), position{x, y}, size{w, h}, velocity{vx, vy}
{}

void Entity::move()
{
    position.setX(x() + vx());
    position.setY(y() + vy());
}

QRectF Entity::boundingRect() const
{
    return QRectF(left(), top(), width(), height());
}
