#include "battlefieldwidget.h"
#include <QPainter>
#include <QPaintEvent>

BattlefieldWidget::BattlefieldWidget(QWidget *parent) : QWidget(parent)
{
    player = nullptr;
    opponent = nullptr;
    setMinimumSize(800, 500);
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
        painter.setBrush(pct > 0.5 ? QColor(46, 204, 113) : pct > 0.25 ? QColor(230, 126, 34) : QColor(231, 76, 60));
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
        painter.setBrush(pct > 0.5 ? QColor(46, 204, 113) : pct > 0.25 ? QColor(230, 126, 34) : QColor(231, 76, 60));
        painter.drawRect(QRectF(pos.x()-40, pos.y()-38, 80 * pct, 10));
    }
}
