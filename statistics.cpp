#include "statistics.h"

Statistics::Statistics(int fails, int wins){
    win = wins;
    fail = fails;
}

Statistics::Statistics(){
    QFormLayout *lay = new QFormLayout(this);
    winLab = new QLabel(QVariant(win).toString());
    failLab = new QLabel(QVariant(fail).toString());\
    gameLab = new QLabel;
    lay->addRow("Игра:", gameLab);
    lay->addRow("Побед:",winLab);
    lay->addRow("Попыток:",failLab);
}

int Statistics::fails(){
    int all = 0;
    for(int i=0; i<listGames.size(); i++){
        all += listGames[i]->fail;
    }
    return all;
}

int Statistics::wins(){
    int all = 0;
    for(int i=0; i<listGames.size(); i++){
        all += listGames[i]->win;
    }
    return all;
}

void Statistics::addStatistic(Statistics *_new){
    listGames.push_back(_new);
    _new->id = listGames.size();
    gameLab->setText(QVariant(listGames.size()).toString());
}

void Statistics::update(){
    winLab->setText(QVariant(wins()).toString());
    failLab->setText(QVariant(fails()).toString());
}

void Statistics::showExtendedStat(){
    QWidget *full = new QWidget;
    full->setMinimumSize(500,400);
    full->setWindowTitle("Полная статистика");
    QGridLayout *grid = new QGridLayout(full);

    QTreeWidget *treeGames = new QTreeWidget;
    treeGames->setHeaderLabels({"Игра","Победа","Поражение"});
//    QTreeWidgetItem *root = new QTreeWidgetItem;
//    root->setText(0,"Игры");
//    treeGames->addTopLevelItem(root);
    for(int i=0; i<listGames.size(); i++){
        QTreeWidgetItem *game = new QTreeWidgetItem;
        game->setText(0,QVariant(listGames[i]->id).toString());
        game->setText(1,QVariant(listGames[i]->win).toString());
        game->setText(2,QVariant(listGames[i]->fail).toString());
//        root->addChild(game);
        treeGames->addTopLevelItem(game);
    }
    grid->addWidget(treeGames);

    full->show();
}
