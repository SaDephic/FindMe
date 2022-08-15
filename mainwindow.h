#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QRandomGenerator>

#include <QMainWindow>

#include <QMessageBox>
#include <QShortcut>

#include <QGridLayout>
#include <QPushButton>

#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include "statistics.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
private:
    Statistics *fullStatistic = nullptr;
    QPushButton *winner = nullptr;
    QWidget *basis = nullptr;
    QVector<QPushButton*> removed;
    Statistics *currentStatistic = nullptr;

public:
    MainWindow();
    ~MainWindow();

private:
    void createArea();
    void createMenu();

public slots:
    void printWIN();
    void printFAIL();
    void recreate();
};

#endif // MAINWINDOW_H
