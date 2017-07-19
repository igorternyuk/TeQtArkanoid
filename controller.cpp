#include "controller.h"
#include "scene.h"
#include <QGraphicsView>
#include <QLCDNumber>
#include <QLabel>

Controller::Controller(QGraphicsView *graphicsView, QLCDNumber *display,
                       QLabel *lblStatus, QObject *parent):
    QObject(parent)
{
    m_scene = new Scene(parent);
    graphicsView->setScene(m_scene);
    connect(m_scene, SIGNAL(scoreChanged(int)), display, SLOT(display(int)));
    connect(m_scene, SIGNAL(statusChanged(QString)), lblStatus, SLOT(setText(QString)));
}

void Controller::newGame()
{
    m_scene->prepareNewGame();
}

void Controller::toggleGame()
{
    switch (m_scene->gameState()) {
        case GameState::INIT:
             m_scene->startScene();
             emit gameStarted();
             break;
        case GameState::PLAY:
             m_scene->stopScene();
             emit gamePaused();
             break;
        case GameState::PAUSE:
             m_scene->startScene();
             emit gameStarted();
             break;
        default:
            break;
    }
}
