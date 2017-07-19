#ifndef PADDLE_H
#define PADDLE_H

#include "arkanoidGlobalDefines.h"
#include "entity.h"

class Paddle: public Entity
{
public:
    explicit Paddle(double x, double y, double w, double h, double vx, double vy,
                    QGraphicsItem *parent = nullptr);
    void moveLeft();
    void moveRight();
    bool isMoving() const;
    void setIsMoving(bool isMoving);
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr) override;
private:
    bool m_isMoving = false;
};

#endif // PADDLE_H
