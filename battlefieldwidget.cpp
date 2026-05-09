#include "battlefieldwidget.h"
#include <QPainter>
#include <QPaintEvent>

BattlefieldWidget::BattlefieldWidget(QWidget *parent) : QWidget(parent)
{
    player = nullptr;
    opponent = nullptr;
    input = nullptr;
    anim = nullptr;
    setMinimumSize(800, 500);
    setFocusPolicy(Qt::StrongFocus);
}

void BattlefieldWidget::setPlayer(Character *p)
{
    player = p;
    update();
}

void BattlefieldWidget::setOpponent(Character *o)
{
    opponent = o;
    update();
}

void BattlefieldWidget::setInputHandler(InputHandler *ih)
{
    input = ih;
}

void BattlefieldWidget::setAnimations(AnimationManager *am)
{
    anim = am;
}

void BattlefieldWidget::keyPressEvent(QKeyEvent *event)
{
    if (input != nullptr) input->keyPressed(event);
}

void BattlefieldWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (input != nullptr) input->keyReleased(event);
}

void BattlefieldWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), QColor(30, 30, 50));

    painter.setPen(QPen(QColor(255, 255, 255, 20), 1));
    for (int x = 0; x < width(); x += 40)
        painter.drawLine(x, 0, x, height());
    for (int y = 0; y < height(); y += 40)
        painter.drawLine(0, y, width(), y);

    if (player != nullptr) {
        QPointF pos = player->position;
        painter.setBrush(QColor(70, 130, 210));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(pos, 24, 24);

        painter.setPen(Qt::white);
        QFont f = painter.font();
        f.setBold(true);
        f.setPointSize(11);
        painter.setFont(f);
        painter.drawText(QRectF(pos.x()-24, pos.y()-24, 48, 48), Qt::AlignCenter, player->name.left(1));

        float pct = player->hpPercent();
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(60, 60, 60));
        painter.drawRect(QRectF(pos.x()-40, pos.y()-38, 80, 10));
        if (pct > 0.5f)       painter.setBrush(QColor(46, 204, 113));
        else if (pct > 0.25f) painter.setBrush(QColor(230, 126, 34));
        else                  painter.setBrush(QColor(231, 76, 60));
        painter.drawRect(QRectF(pos.x()-40, pos.y()-38, 80 * pct, 10));
    }

    if (opponent != nullptr) {
        QPointF pos = opponent->position;
        painter.setBrush(QColor(210, 70, 70));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(pos, 24, 24);

        painter.setPen(Qt::white);
        QFont f = painter.font();
        f.setBold(true);
        f.setPointSize(11);
        painter.setFont(f);
        painter.drawText(QRectF(pos.x()-24, pos.y()-24, 48, 48), Qt::AlignCenter, opponent->name.left(1));

        float pct = opponent->hpPercent();
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(60, 60, 60));
        painter.drawRect(QRectF(pos.x()-40, pos.y()-38, 80, 10));
        if (pct > 0.5f)       painter.setBrush(QColor(46, 204, 113));
        else if (pct > 0.25f) painter.setBrush(QColor(230, 126, 34));
        else                  painter.setBrush(QColor(231, 76, 60));
        painter.drawRect(QRectF(pos.x()-40, pos.y()-38, 80 * pct, 10));
    }

    if (anim != nullptr) {
        for (HitFlash &flash : anim->flashes) {
            float alpha = (float)flash.ttl / 12.0f;
            QColor c = flash.color;
            c.setAlphaF(alpha);
            painter.setBrush(c);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(flash.pos, 18, 18);
        }

        for (FloatingText &t : anim->texts) {
            float alpha = (float)t.ttl / 30.0f;
            QColor c = t.color;
            c.setAlphaF(alpha);
            painter.setPen(c);
            QFont f = painter.font();
            f.setBold(true);
            f.setPointSize(10);
            painter.setFont(f);
            painter.drawText(t.pos, t.text);
        }

        for (Particle &p : anim->particles) {
            float alpha = (float)p.ttl / 40.0f;
            QColor c = p.color;
            c.setAlphaF(alpha);
            painter.setBrush(c);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(p.pos, p.radius, p.radius);
        }
    }
}
