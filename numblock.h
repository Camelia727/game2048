#ifndef NUMBLOCK_H
#define NUMBLOCK_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class NumBlock;
}

class NumBlock : public QWidget
{
    Q_OBJECT

public:
    explicit NumBlock(QWidget *parent = nullptr);
    ~NumBlock();
    void setNum(const int n);
    void setTheme(const QColor grid, const QColor shadow);
    int getNum() const {return num;}
    int getTheme() const {return theme;}

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::NumBlock *ui;
    int num;
    int theme;
    QColor gridColor;
    QColor shadowColor;
};

#endif // NUMBLOCK_H
