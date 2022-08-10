#include "mainwindow.h"

MainWindow::MainWindow(){
    setWindowTitle("FIND ME");
    setFixedSize(QSize(325,325));

    basis = new QWidget;
    setCentralWidget(basis);

    QShortcut *shortreboot = new QShortcut(this);
    shortreboot->setKey(Qt::Key_F5);
    connect(shortreboot,&QShortcut::activated,this,&MainWindow::recreate);

    createArea();
}

MainWindow::~MainWindow(){
    delete winner;
    while(!removed.isEmpty()){
        delete removed.first();
        removed.removeFirst();
    }
}

void MainWindow::createArea(){
    QGridLayout *grid = new QGridLayout(basis);
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
}

void MainWindow::printWIN(){
    static_cast<QPushButton*>(sender())->setStyleSheet("background-color:green");
    QMessageBox message;
    message.setWindowFlag(Qt::WindowStaysOnTopHint);
    message.setWindowTitle("Congratulation");
    message.setText("YOU WIN!\nFAILS:" + QVariant(countFails+1).toString());
    message.setIcon(QMessageBox::Information);
    message.exec();
    foreach(QPushButton *cur,removed){
        cur->setEnabled(false);
    }
    winner->setEnabled(false);
}

void MainWindow::printFAIL(){
    static_cast<QPushButton*>(sender())->setStyleSheet("background-color:red");
    static_cast<QPushButton*>(sender())->setEnabled(false);
    countFails++;
}

void MainWindow::recreate(){
    countFails = 0;

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
