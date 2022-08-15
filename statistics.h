#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include <QObject>

#include <QFormLayout>
#include <QLabel>

#include <QTreeWidget>

class Statistics : public QWidget{
    Q_OBJECT
public:
    int id = 0;
    int win = 0;
    int fail = 0;
private:
    QLabel *gameLab = nullptr;
    QLabel *winLab = nullptr;
    QLabel *failLab = nullptr;
    QVector<Statistics*> listGames;
public:
    Statistics(int fails, int wins);
    Statistics();
    int fails();
    int wins();
    void addStatistic(Statistics *_new);
    void update();
public slots:
    void showExtendedStat();
};

#endif // STATISTICS_H
