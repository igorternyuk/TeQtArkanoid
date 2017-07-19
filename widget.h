#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Controller;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    enum {SCREEN_WIDTH = 1154, SCREEN_HEIGHT = 625};
    Ui::Widget *ui;
    Controller *m_controller;
    void configureWidgets();
    void connectWidgets();
};

#endif // WIDGET_H
