#ifndef BRICK_H
#define BRICK_H

#include "entity.h"

class Brick : public Entity
{
public:
    explicit Brick(double x, double y, double width, double height,
                   QGraphicsItem *parent = nullptr);
    inline void hit(){ m_health -= m_damage; }
    inline bool isBroken(){ return m_health <= 0; }
    inline int scoreIncrement() { return m_scoreIncrement; }
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr) override;
private:
    enum class Type{GREEN, BLUE, MAGENTA, YELLOW, RED};
    Type m_type;
    int m_damage;
    int m_scoreIncrement;
    int m_health = 100;
};

#endif // BRICK_H
