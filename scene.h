#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <vector>
#include "arkanoidGlobalDefines.h"

#ifdef DEBUG
class QGraphicsSceneMouseEvent;
#endif
class QKeyEvent;
class TeThread;
class Ball;
class Paddle;
class Brick;

enum class GameState{ INIT, PLAY, PAUSE, VICTORY, DEFEAT};

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();
    inline bool isGamePaused(){
        return m_gameState == GameState::PAUSE ||
               m_gameState == GameState::INIT;
    }

signals:
    void scoreOrStatusChanged(QString msg);
public slots:
    void startScene();
    void stopScene();
    void prepareNewGame();
    void updateScene();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
#ifdef DEBUG
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
#endif
private:
    enum{
        BALL_X = FIELD_WIDTH / 2,
        BALL_Y = FIELD_HEIGHT / 2,
        BALL_RADIUS = 10,
        BALL_VX  = 2,
        BALL_VY = -3,
        BRICK_WIDTH = 60,
        BRICK_HEIGHT = 25,
        BRICKS_ROW_COUNT = 5,
        BRICKS_COLUMN_COUNT = 14,
        BRICKS_VERTICAL_GAP = 2,
        BRICKS_HORIZONTAL_GAP = 2,
        BRICKS_LEFT = 90,
        BRICKS_TOP = 25
    };
    static struct PaddleConsts
    {
        double PADDLE_X = FIELD_RIGHT * 0.5;
        double PADDLE_Y = FIELD_BOTTOM * 7 / 8;
        double PADDLE_WIDTH = 150;
        double PADDLE_HEIGHT = 15;
        double PADDLE_VX = 15;
        double PADDLE_VY = 0;
    } paddle_const;

    int m_score = 0;
    GameState m_gameState;
    Ball *m_ball;
    Paddle *m_paddle;
    std::vector<Brick*> m_bricks;
    TeThread *m_thread;
    void createObjects();
    void createBricksSetup();
    void removeBricks();
    void configureObjects();
    void connectObjects();
    void handleBallPaddleCollision();
    bool handleBallBrickCollision(Brick *brick);
    void handleCollisions();
    void removeBrokenBricks();
    bool isWin() const;
};

#endif // SCENE_H
