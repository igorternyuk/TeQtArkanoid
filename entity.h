#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsItem>
// базовый класс для всех сушностей

class Entity : public QGraphicsItem
{
public:
    explicit Entity(double x, double y, double w, double h, double vx, double vy,
                    QGraphicsItem *parent = nullptr);
    inline void setX(double x){ position.setX(x); }
    inline void setY(double y){ position.setY(y); }
    inline void setVx(double vx){ velocity.setX(vx); }
    inline void setVy(double vy){ velocity.setY(vy); }
    inline void setWidth(double w) { size.setX(w); }
    inline void setHeight(double h) { size.setY(h); }
    inline double x() const { return position.x(); }
    inline double y() const { return position.y(); }
    inline double left() const { return x() - width() / 2; }
    inline double top() const { return y() - height() / 2; }
    inline double right() const { return x() + width() / 2;}
    inline double bottom() const { return y() + height() / 2; }
    inline double width() const { return size.x(); }
    inline double height() const { return size.y(); }
    inline double vx() const { return velocity.x(); }
    inline double vy() const { return velocity.y(); }
protected:
    QPointF position, size, velocity;
    virtual void move();
    virtual QRectF boundingRect() const override;
};

#endif // ENTITY_H
