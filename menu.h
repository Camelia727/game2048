#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "button.h"
#include "volumnslider.h"

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private:
    Ui::Menu *ui;
    QColor mainbackColor;
    Button* themeBtn;
    Button* resetBtn;
    Button* returnBtn;
    Button* exitBtn;
    VolumnSlider* volumnSlider;
protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // MENU_H
