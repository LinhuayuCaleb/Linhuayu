#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QVector>
#include <QMap>
#include <QSet>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;

    static const int TILE = 32;
    static const int MAP_W = 20;
    static const int MAP_H = 15;

    enum BlockType {
        AIR = 0,
        DIRT = 1,
        STONE = 2
    };

    int map[MAP_H][MAP_W];

    int playerX = 5;
    int playerY = 5;

    QPixmap tilemap;

    QSet<int> keys;

    QTimer moveTimer;
    bool canMove = true;

    QMap<int,int> inventory;

private:
    QRect getTile(int type);
    bool isBlocked(int x, int y);
    void initMap();
};

#endif
