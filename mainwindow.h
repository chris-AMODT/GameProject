#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void startGame();
    void exitGame();

private:
    QLabel      *titleLabel;
    QPushButton *startBtn;
    QPushButton *exitBtn;
};
