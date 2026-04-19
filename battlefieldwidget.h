#pragma once

#include <QWidget>
#include "character.h"

class BattlefieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BattlefieldWidget(QWidget *parent = nullptr);

    void setPlayer(Character *p);
    void setOpponent(Character *o);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Character *player;
    Character *opponent;
};
