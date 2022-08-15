#include "mainwindow.h"

MainWindow::MainWindow(){
    setWindowTitle("FIND ME");

//    setFixedSize(QSize(325,325));
    fullStatistic = new Statistics;
    currentStatistic = new Statistics(0,0);
    fullStatistic->addStatistic(currentStatistic);

    basis = new QWidget;
    setCentralWidget(basis);

    QShortcut *shortreboot = new QShortcut(this);
    shortreboot->setKey(Qt::Key_F5);
    connect(shortreboot,&QShortcut::activated,this,&MainWindow::recreate);

    createMenu();
    createArea();
}

MainWindow::~MainWindow(){
    delete winner;
    while(!removed.isEmpty()){
        delete removed.first();
        removed.removeFirst();
    }
}

void MainWindow::createArea(){\
    QHBoxLayout *hlay = new QHBoxLayout(basis);
    QGridLayout *grid = new QGridLayout;
    winner = new QPushButton("Ok");
    winner->setFixedSize(100,100);
    connect(winner,&QPushButton::clicked,this,&MainWindow::printWIN);

    int randpos = QRandomGenerator::global()->bounded(0, 9);
    int counter = 0;
    for(int r=0; r<3; r++){
        for(int c=0; c<3; c++){
            if(counter == randpos)
                grid->addWidget(winner,r,c);
            else{
                QPushButton *looser = new QPushButton("Ok");
                removed.push_back(looser);
                looser->setFixedSize(100,100);
                connect(looser,&QPushButton::clicked,this,&MainWindow::printFAIL);
                grid->addWidget(looser,r,c);
            }
            counter++;
        }
    }
    hlay->addLayout(grid);
    hlay->addWidget(fullStatistic);
}

void MainWindow::createMenu(){
    QMenuBar *menu = new QMenuBar;
    setMenuBar(menu);
    QMenu *game = new QMenu("Игра");
    menu->addMenu(game);
    QAction *reset = new QAction("Перезапустить");
    connect(reset,&QAction::triggered,this,&MainWindow::recreate);
    game->addAction(reset);

    QAction *fullstat = new QAction("Полная статистика");
    connect(fullstat,&QAction::triggered,fullStatistic,&Statistics::showExtendedStat);
    game->addAction(fullstat);
}

void MainWindow::printWIN(){
    static_cast<QPushButton*>(sender())->setStyleSheet("background-color:green");
    QMessageBox message;
    message.setWindowFlag(Qt::WindowStaysOnTopHint);
    message.setWindowTitle("Congratulation");
    message.setText("YOU WIN!\nFAILS:" + QVariant(currentStatistic->fail+1).toString());
    message.setIcon(QMessageBox::Information);
    message.exec();

    currentStatistic->win = 1;

    foreach(QPushButton *cur,removed){
        cur->setEnabled(false);
    }
    winner->setEnabled(false);

    fullStatistic->update();
}

void MainWindow::printFAIL(){
    static_cast<QPushButton*>(sender())->setStyleSheet("background-color:red");
    static_cast<QPushButton*>(sender())->setEnabled(false);
    currentStatistic->fail++;
    fullStatistic->update();
}

void MainWindow::recreate(){
    currentStatistic = new Statistics(0,0);
    fullStatistic->addStatistic(currentStatistic);

    while(!removed.isEmpty()){
        delete removed.first();
        removed.removeFirst();
    }

    delete basis->layout();

    winner->setStyleSheet("background-color:none");
    winner->setEnabled(true);

    createArea();
    update();
}
