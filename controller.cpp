#include "controller.h"
#include "scene.h"
#include <QGraphicsView>
#include <QLCDNumber>

Controller::Controller(QGraphicsView *graphicsView, QLCDNumber *display, QObject *parent):
    QObject(parent)
{
    m_scene = new Scene(parent);
    graphicsView->setScene(m_scene);
    connect(m_scene, SIGNAL(scoreOrStatusChanged(QString)), display, SLOT(display(QString)));
}

void Controller::newGame()
{
    m_scene->prepareNewGame();
}

void Controller::toggleGame()
{
    if(m_scene->isGamePaused())
    {
        m_scene->startScene();
    }
    else
    {
        m_scene->stopScene();
    }
}
