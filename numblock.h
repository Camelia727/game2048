#ifndef NUMBLOCK_H
#define NUMBLOCK_H

#include <QWidget>

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
    void setTheme(const int t);
    int getNum() const {return num;}
    int getTheme() const {return theme;}

private:
    Ui::NumBlock *ui;
    int num;
    int theme;
};

#endif // NUMBLOCK_H
