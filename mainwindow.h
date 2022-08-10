#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QRandomGenerator>

#include <QMainWindow>

#include <QMessageBox>
#include <QShortcut>

#include <QGridLayout>
#include <QPushButton>

class MainWindow : public QMainWindow{
    Q_OBJECT
private:
    QPushButton *winner = nullptr;
    QWidget *basis = nullptr;
    QVector<QPushButton*> removed;
    int countFails = 0;

public:
    MainWindow();
    ~MainWindow();

private:
    void createArea();

public slots:
    void printWIN();
    void printFAIL();
    void recreate();
};

#endif // MAINWINDOW_H
