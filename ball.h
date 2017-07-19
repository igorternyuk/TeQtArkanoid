#ifndef BALL_H
#define BALL_H

#include "arkanoidGlobalDefines.h"
#include "entity.h"


class Ball : public Entity
{
public:
    explicit Ball(double x, double y, double r, double vx, double vy,
                  QGraphicsItem *parent = nullptr);
    void move();

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr) override;
};

#endif // BALL_H
