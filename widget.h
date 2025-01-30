#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include "button.h"
#include "numblock.h"
#include "qlabel.h"
#include "volumnslider.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QColor getGridColor() const {return gridColor;}
    QColor getGridshadowColor() const {return gridshadowColor;}

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::Widget *ui;

    bool moving;
    bool menuOpen;
    int curScore;
    int topScore;
    QLabel* curscoreLabel;
    QLabel* topscoreLabel;
    QMediaPlayer* player;
    QAudioOutput* audio;
    QTimer* durationTimer;
    QColor backgroundColor;
    QColor mainbackColor;
    QColor mainbtnColor;
    QColor gridColor;
    QColor gridbackColor;
    QColor gridblockColor;
    QColor backshadowColor;
    QColor mainshadowColor;
    QColor gridshadowColor;
    QWidget* menu;
    Button* recallBtn;
    Button* menuBtn;
    Button* themeBtn;
    Button* resetBtn;
    Button* returnBtn;
    Button* exitBtn;
    VolumnSlider* volumnSlider;

    QList<QUrl> bgms;
    QList<QList<bool>> merge;
    QList<QList<int>> numbers;
    QList<QList<NumBlock*>> grids;

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void moveGrid(int x1, int y1, int x2, int y2);
    bool moveAnimationX(QList<QList<QPoint>> moves);
    bool moveAnimationY(QList<QList<QPoint>> moves);
    void createGrid();
    void updateCurScore(int score);
    void updateTopScore();
    bool isEnd() const;
    void gamePauseOn();
    void gamePauseOff();
    void gameEnd();
    void saveArchive();
    void loadArchive();
    void newGame();

public slots:
    void playBgm(QMediaPlayer::MediaStatus status);
    void acceptMove();
    void recall();
    void openMenu();
    void changeTheme();
    void reset();
    void closeMenu();
    void exit();
    void changeVolumn(int volumn);

};
#endif // WIDGET_H
