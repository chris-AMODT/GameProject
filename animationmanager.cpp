#include "animationmanager.h"
#include <QRandomGenerator>
#include <QtMath>

AnimationManager::AnimationManager(QObject *parent) : QObject(parent) {}

void AnimationManager::spawnHit(QPointF pos, int damage)
{
    HitFlash f;
    f.pos = pos;
    f.color = damage >= 20 ? QColor(255, 60, 60) : QColor(255, 170, 60);
    f.ttl = 12;
    flashes.append(f);

    FloatingText t;
    int rx = QRandomGenerator::global()->bounded(30) - 15;
    t.pos = QPointF(pos.x() + rx, pos.y() - 20);
    t.text = "-" + QString::number(damage);
    t.color = f.color;
    t.ttl = 30;
    texts.append(t);
}

void AnimationManager::spawnDeath(QPointF pos, QColor color)
{
    for (int i = 0; i < 20; i++) {
        Particle p;
        p.pos = pos;
        float angle = QRandomGenerator::global()->bounded(360) * 3.14159f / 180.0f;
        float spd = 2.0f + QRandomGenerator::global()->bounded(4);
        p.vel = QPointF(spd * qCos(angle), spd * qSin(angle));
        p.color = color;
        p.radius = 3.0f + QRandomGenerator::global()->bounded(5);
        p.ttl = 20 + QRandomGenerator::global()->bounded(20);
        particles.append(p);
    }
}

void AnimationManager::tick()
{
    for (int i = flashes.size() - 1; i >= 0; i--) {
        flashes[i].ttl--;
        if (flashes[i].ttl <= 0) flashes.removeAt(i);
    }

    for (int i = texts.size() - 1; i >= 0; i--) {
        texts[i].ttl--;
        texts[i].pos.ry() -= 0.8;
        if (texts[i].ttl <= 0) texts.removeAt(i);
    }

    for (int i = particles.size() - 1; i >= 0; i--) {
        particles[i].pos += particles[i].vel;
        particles[i].vel.ry() += 0.25;
        particles[i].vel *= 0.93;
        particles[i].ttl--;
        if (particles[i].ttl <= 0) particles.removeAt(i);
    }
}
