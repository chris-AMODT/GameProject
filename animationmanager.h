#pragma once

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QColor>
#include <QString>

struct HitFlash {
    QPointF pos;
    QColor color;
    int ttl;
};

struct FloatingText {
    QPointF pos;
    QString text;
    QColor color;
    int ttl;
};

struct Particle {
    QPointF pos;
    QPointF vel;
    QColor color;
    float radius;
    int ttl;
};

class AnimationManager : public QObject
{
    Q_OBJECT

public:
    explicit AnimationManager(QObject *parent = nullptr);

    void spawnHit(QPointF pos, int damage);
    void spawnDeath(QPointF pos, QColor color);
    void tick();

    QVector<HitFlash>     flashes;
    QVector<FloatingText> texts;
    QVector<Particle>     particles;
};
