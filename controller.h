#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "arkanoidGlobalDefines.h"

class Scene;
class QLCDNumber;
class QGraphicsView;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QGraphicsView *graphicsView, QLCDNumber *display,
                      QObject *parent = nullptr);
signals:
    void gameStarted();
    void gamePaused();
public slots:
    void newGame();
    void toggleGame();

private:
    Scene *m_scene;
};

#endif // CONTROLLER_H
