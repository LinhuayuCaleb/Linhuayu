#include "mainwindow.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QtMath>
#include <algorithm>

static const int WORLD = 1200;
static const int PLAYER_R = 10;
static const int ENEMY_R = 9;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1000,800);

    playerPos = QPointF(300,300);
    camera = playerPos;

    spawnWorld();

    for(int i=0;i<15;i++)
        spawnEnemy();

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::gameLoop);
    timer->start(16);
}

MainWindow::~MainWindow(){}

// ================= WORLD =================
void MainWindow::spawnWorld()
{
    stones.clear();

    for(int i=0;i<50;i++)
    {
        QRect r(
            QRandomGenerator::global()->bounded(WORLD),
            QRandomGenerator::global()->bounded(WORLD),
            QRandomGenerator::global()->bounded(40,90),
            QRandomGenerator::global()->bounded(40,90)
            );

        stones.push_back({r});
    }
}

// ================= ENEMY =================
void MainWindow::spawnEnemy()
{
    Enemy e;
    e.pos = QPointF(
        QRandomGenerator::global()->bounded(WORLD),
        QRandomGenerator::global()->bounded(WORLD)
        );
    enemies.push_back(e);
}

// ================= COLLISION =================
bool MainWindow::collideStone(QPointF p)
{
    QRect r(p.x()-PLAYER_R, p.y()-PLAYER_R, PLAYER_R*2, PLAYER_R*2);

    for(const Stone &s:stones)
        if(s.rect.intersects(r))
            return true;

    return false;
}

// ================= SAFE MOVE =================
QPointF MainWindow::safeMove(QPointF pos, QPointF vel)
{
    QPointF nx = pos + QPointF(vel.x(),0);
    if(!collideStone(nx)) pos = nx;

    QPointF ny = pos + QPointF(0,vel.y());
    if(!collideStone(ny)) pos = ny;

    return pos;
}

// ================= PLAYER =================
void MainWindow::updatePlayer()
{
    QPointF v(0,0);

    if(w) v.ry()-=3;
    if(s) v.ry()+=3;
    if(a) v.rx()-=3;
    if(d) v.rx()+=3;

    playerPos = safeMove(playerPos,v);
}

// ================= ENEMY AI =================
void MainWindow::updateEnemies()
{
    for(Enemy &e:enemies)
    {
        QPointF dir = playerPos - e.pos;
        float len = qSqrt(dir.x()*dir.x()+dir.y()*dir.y());

        if(len>0)
            dir/=len;

        QPointF move = dir * 1.4;
        QPointF next = safeMove(e.pos,move);

        // 防卡死
        if((next - e.pos).manhattanLength() < 0.1)
        {
            e.stuck++;
            if(e.stuck > 20)
            {
                next += QPointF(
                    QRandomGenerator::global()->bounded(-30,30),
                    QRandomGenerator::global()->bounded(-30,30)
                    );
                e.stuck = 0;
            }
        }

        e.pos = next;
    }
}

// ================= BULLETS =================
void MainWindow::updateBullets()
{
    for(auto &b:bullets)
    {
        QPointF next = b.pos + b.vel;

        if(collideStone(next))
        {
            b.life = 0;
            continue;
        }

        b.pos = next;
        b.life--;

        if(!b.fromEnemy)
        {
            for(Enemy &e:enemies)
            {
                if(QLineF(b.pos,e.pos).length()<10)
                {
                    e.hp -= 20;
                    b.life = 0;
                }
            }
        }
        else
        {
            if(QLineF(b.pos,playerPos).length()<10)
            {
                playerHp -= 2;
                b.life = 0;
            }
        }
    }

    bullets.erase(std::remove_if(bullets.begin(),bullets.end(),
                                 [](Bullet &b){return b.life<=0;}), bullets.end());
}

// ================= LOOP =================
void MainWindow::gameLoop()
{
    updatePlayer();
    updateEnemies();
    updateBullets();

    camera += (playerPos - camera)*0.08;

    update();
}

// ================= RENDER =================
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.translate(width()/2-camera.x(),
                height()/2-camera.y());

    // stones
    p.setBrush(QColor(80,80,80));
    for(const Stone &s:stones)
        p.drawRoundedRect(s.rect,6,6);

    // player
    p.setBrush(QColor(255,120,180));
    p.drawEllipse(playerPos,PLAYER_R,PLAYER_R);

    // enemies
    p.setBrush(QColor(100,180,255));
    for(const Enemy &e:enemies)
        p.drawEllipse(e.pos,ENEMY_R,ENEMY_R);

    // bullets
    for(const Bullet &b:bullets)
    {
        p.setBrush(b.fromEnemy ? Qt::cyan : Qt::yellow);
        p.drawEllipse(b.pos,4,4);
    }

    // UI
    p.resetTransform();
    p.setBrush(Qt::red);
    p.drawRect(20,20,playerHp*2,15);
}

// ================= INPUT =================
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_W) w=true;
    if(e->key()==Qt::Key_S) s=true;
    if(e->key()==Qt::Key_A) a=true;
    if(e->key()==Qt::Key_D) d=true;
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_W) w=false;
    if(e->key()==Qt::Key_S) s=false;
    if(e->key()==Qt::Key_A) a=false;
    if(e->key()==Qt::Key_D) d=false;
}
