#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QPointF>
#include <QRect>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;

private slots:
    void gameLoop();

private:
    struct Bullet {
        QPointF pos;
        QPointF vel;
        bool fromEnemy;
        int life = 120;
    };

    struct Enemy {
        QPointF pos;
        float hp = 50;
        int stuck = 0;
    };

    struct Stone {
        QRect rect;
    };

private:
    void spawnWorld();
    void spawnEnemy();
    void updatePlayer();
    void updateEnemies();
    void updateBullets();

    bool collideStone(QPointF p);
    QPointF safeMove(QPointF pos, QPointF vel);

private:
    QPointF playerPos;
    QPointF camera;

    QVector<Bullet> bullets;
    QVector<Enemy> enemies;
    QVector<Stone> stones;

    QTimer *timer;

    bool w=false,a=false,s=false,d=false;

    int playerHp = 100;
};

#endif
