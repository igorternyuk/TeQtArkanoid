#include "brick.h"
#include <cmath>
#include <ctime>
#include <QPainter>

Brick::Brick(double x, double y, double width, double height, QGraphicsItem *parent):
    Entity(x, y, width, height, 0.0, 0.0, parent)
{
    int rnd = rand() % 100;
    if(rnd < 35)
    {
        m_type = Type::GREEN;
        m_damage = 100;
        m_scoreIncrement = 5;
    }
    else if(rnd < 50)
    {
        m_type = Type::BLUE;
        m_damage = 50;
        m_scoreIncrement = 10;
    }
    else if(rnd < 60)
    {
        m_type = Type::MAGENTA;
        m_damage = 34;
        m_scoreIncrement = 20;
    }
    else if(rnd < 80)
    {
        m_type = Type::YELLOW;
        m_damage = 25;
        m_scoreIncrement = 25;
    }
    else
    {
        m_type = Type::RED;
        m_damage = 20;
        m_scoreIncrement = 50;
    }
}

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    if(!isBroken())
      {
        switch(m_type)
        {
            case Type::GREEN:
                painter->setBrush(Qt::green);
                break;
            case Type::BLUE:
                painter->setBrush(Qt::cyan);
                break;
            case Type::MAGENTA:
                painter->setBrush(Qt::magenta);
                break;
            case Type::YELLOW:
                painter->setBrush(Qt::yellow);
                break;
            case Type::RED:
                painter->setBrush(Qt::red);
                break;
        }
        painter->drawRect(boundingRect());
        painter->setBrush(Qt::NoBrush);
    }
}
