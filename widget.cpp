#include "widget.h"
#include "ui_widget.h"
#include "controller.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_controller = new Controller(ui->graphicsView, ui->lcdDisplay, ui->lblGameStatus, this);
    configureWidgets();
    connectWidgets();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::configureWidgets()
{
    this->setWindowTitle(QStringLiteral("QtArkanoid"));
    this->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    ui->lcdDisplay->setDigitCount(NUM_DIGITS);
    ui->lcdDisplay->display(0);
    ui->lcdDisplay->setAutoFillBackground(true);
    QPalette pal= palette();
    pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::green);
    pal.setColor(QPalette::Normal, QPalette::Window, Qt::black);
    ui->lcdDisplay->setPalette(pal);
}

void Widget::connectWidgets()
{
    connect(ui->btnNewGame, SIGNAL(clicked(bool)), m_controller, SLOT(newGame()));
    connect(ui->btnPause, SIGNAL(clicked(bool)), m_controller, SLOT(toggleGame()));
    connect(m_controller, &Controller::gameStarted, [&](){
        ui->btnPause->setText(QStringLiteral("Pause game"));
    });
    connect(m_controller, &Controller::gamePaused, [&](){
        ui->btnPause->setText(QStringLiteral("Start game"));
    });
}
