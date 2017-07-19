#include "scene.h"
#include "ball.h"
#include "paddle.h"
#include "brick.h"
#include "tethread.h"
#include <algorithm>
#include <QKeyEvent>
#ifdef DEBUG
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#endif

Scene::Scene(QObject *parent):
    QGraphicsScene(FIELD_LEFT, FIELD_TOP, FIELD_WIDTH, FIELD_HEIGHT, parent),
    m_score(0), m_gameState(GameState::INIT)
{
    createObjects();
    configureObjects();
    connectObjects();
    m_thread->start();
}

Scene::~Scene()
{   
    qDebug() << "Работает деструктор сцены";
    m_thread->quit();
    if(!m_thread->wait(3000)) //Wait until it actually has terminated (max. 3 sec)
    {
        m_thread->terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
        m_thread->wait(); //We have to wait again here!
    }
    qDebug() << "Закрыли поток";
    delete m_ball;
    delete m_paddle;
    removeBricks();
    qDebug() << "Освобождение памяти исключений не вызвало";
}

Scene::PaddleConsts Scene::paddle_const;

void Scene::startScene()
{
    if(m_gameState == GameState::INIT || m_gameState == GameState::PAUSE)
    {
        m_gameState = GameState::PLAY;
        emit scoreOrStatusChanged(QString::number(m_score));
        m_thread->start();
    }
}

void Scene::stopScene()
{
    if(m_gameState == GameState::PLAY)
    {
        m_gameState = GameState::PAUSE;
        emit scoreOrStatusChanged(QStringLiteral("GAME PAUSED"));
        m_thread->terminate();
    }
}

void Scene::createObjects()
{
    m_ball = new Ball(BALL_X, BALL_Y, BALL_RADIUS, BALL_VX, BALL_VY);
    m_paddle = new Paddle(paddle_const.PADDLE_X, paddle_const.PADDLE_Y,
                          paddle_const.PADDLE_WIDTH, paddle_const.PADDLE_HEIGHT,
                          paddle_const.PADDLE_VX, paddle_const.PADDLE_VY);
    createBricksSetup();
    m_thread = new TeThread(TIMER_DELAY, this);
}

void Scene::createBricksSetup()
{
    if(!m_bricks.empty())
        removeBricks();
    int k = 0;
    for(int r = 0; r < BRICKS_ROW_COUNT; ++r)
    {
        for(int c = 0; c < BRICKS_COLUMN_COUNT; ++c)
        {
            double x = BRICKS_LEFT + c * (BRICK_WIDTH + BRICKS_HORIZONTAL_GAP);
            double y = BRICKS_TOP + r * (BRICK_HEIGHT + BRICKS_VERTICAL_GAP);
            qDebug() << "Ladrillo numero " << ++k << ": x = " << x << " y = " << y;
            Brick *brick = new Brick(x, y, BRICK_WIDTH, BRICK_HEIGHT);
            //this->addItem(brick);
            m_bricks.push_back(brick);
        }
    }
}

void Scene::removeBricks()
{
    for(auto &b: m_bricks)
    {
        this->removeItem(b);
        delete b;
    }
    m_bricks.erase(m_bricks.begin(), m_bricks.end());
    m_bricks.clear();
}

void Scene::configureObjects()
{
    this->addItem(m_ball);
    this->addItem(m_paddle);
    for(auto &b: m_bricks)
    {
        this->addItem(b);
    }
}

void Scene::connectObjects()
{
    connect(m_thread, SIGNAL(timeOut()), this, SLOT(updateScene()));
}

void Scene::prepareNewGame()
{
    m_score = 0;
    emit scoreOrStatusChanged(QString::number(m_score));
    m_gameState = GameState::PLAY;
    m_ball->setX(BALL_X);
    m_ball->setY(BALL_Y);
    m_paddle->setX(paddle_const.PADDLE_X);
    m_paddle->setY(paddle_const.PADDLE_Y);
    createBricksSetup();
}

void Scene::handleBallPaddleCollision()
{
    if(!m_ball->collidesWithItem(m_paddle)) return;
    if(m_paddle->isMoving())
    {
        m_ball->setVx(fabs(m_paddle->vx()) / m_paddle->vx() * fabs(m_ball->vx()));
    }
    m_ball->setVy(-m_ball->vy());
}

bool Scene::handleBallBrickCollision(Brick *brick)
{
    if(!m_ball->collidesWithItem(brick) || brick->isBroken()) return false;
    qDebug() << "Ladrillo fue tocado";
    double overlapLeft = m_ball->right() - brick->left();
    double overlapRight = m_ball->left() - brick->right();
    double overlapTop = m_ball->bottom() - brick->top();
    double overlapBottom = m_ball->top() - brick->bottom();

    double minOverlapX = qMin(overlapLeft, overlapRight);
    double minOverlapY = qMin(overlapTop, overlapBottom);

    if(minOverlapX < minOverlapY)
    {
        m_ball->setVy(-m_ball->vy());
    }
    else if(minOverlapX > minOverlapY)
    {
        m_ball->setVx(-m_ball->vx());
    }
    else
    {
        m_ball->setVy(-m_ball->vy());
        m_ball->setVx(-m_ball->vx());
    }
    brick->hit();
    if(brick->isBroken())
    {
        m_score += brick->scoreIncrement();
        emit scoreOrStatusChanged(QString::number(m_score));
    }
    removeBrokenBricks(); //Подчищаем кирпичи
#ifdef DEBUG
    qDebug() << "numBricks = " << m_bricks.size();
#endif
    return true;
}

void Scene::removeBrokenBricks()
{
    auto it = std::remove_if(m_bricks.begin(), m_bricks.end(), [&](Brick *&brick){
        bool isBroken = brick->isBroken();
        if(isBroken)
        {
            this->removeItem(brick);
            delete brick;
        }
        return isBroken;
    });
    m_bricks.erase(it, m_bricks.end());
}

bool Scene::isWin() const
{
    bool result = true;
    for(auto &b: m_bricks)
    {
        if(!b->isBroken())
        {
            result = false;
            break;
        }
    }
    return result;
}

///////////////////////Main loop of the game///////////////////

void Scene::updateScene()
{
    //Game logic
#ifdef DEBUG
    //qDebug() << "Ball: x = " << m_ball->x() << "y = " << m_ball->x();
#endif

    if(m_gameState == GameState::PLAY)
    {
        m_ball->move();
        //Обрабатываем столкновения мячика с ракеткой
        handleBallPaddleCollision();
        //Обрабатываем столкновения мячика с кирпичами
        for(auto &b: m_bricks)
        {
            if(handleBallBrickCollision(b))
            {
                break;
            }
        }
        if(isWin())
        {
            m_gameState = GameState::VICTORY;
            emit scoreOrStatusChanged(QStringLiteral("YOU WON!"));
            m_thread->terminate();
        }
        /*else if(m_ball->bottom() > m_paddle->bottom())
        {
            m_gameState = GameState::DEFEAT;
            emit scoreOrStatusChanged(QStringLiteral("YOU LOST!"));
            m_thread->terminate();
        }*/
    }
    update();
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(m_gameState != GameState::PLAY) return;
    int key = event->key();
    switch(key)
    {
        case Qt::Key_Left:
            m_paddle->setIsMoving(true);
            m_paddle->moveLeft();
#ifdef DEBUG
           // qDebug() << "The paddle moves left";
           // qDebug() << "paddle: x = " << m_paddle->x() << "y = " << m_paddle->y();
#endif
            break;
        case Qt::Key_Right:
            m_paddle->setIsMoving(true);
            m_paddle->moveRight();
#ifdef DEBUG
            //qDebug() << "The paddle moves right";
            //qDebug() << "paddle: x = " << m_paddle->x() << "y = " << m_paddle->y();
#endif
            break;
    }

}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
    m_paddle->setIsMoving(false);
    event->accept();
}

#ifdef DEBUG
void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "Cursor: x = " << event->pos().x() << "y = " << event->pos().y();
}
#endif
