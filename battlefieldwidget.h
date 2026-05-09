#pragma once

#include <QWidget>
#include "character.h"
#include "inputhandler.h"
#include "animationmanager.h"

class BattlefieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BattlefieldWidget(QWidget *parent = nullptr);

    void setPlayer(Character *p);
    void setOpponent(Character *o);
    void setInputHandler(InputHandler *ih);
    void setAnimations(AnimationManager *am);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Character        *player;
    Character        *opponent;
    InputHandler     *input;
    AnimationManager *anim;
};
