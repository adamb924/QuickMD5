#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("QuickMD5"));

    connect( ui->dropTarget1, SIGNAL(textChanged(QString)), this, SLOT(hashChanged()));
    connect( ui->dropTarget2, SIGNAL(textChanged(QString)), this, SLOT(hashChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hashChanged()
{
    if( ui->dropTarget1->text() == ui->dropTarget2->text() )
    {
        ui->dropTarget1->setStyleSheet("background-color: rgb(0,255,140);");
        ui->dropTarget2->setStyleSheet("background-color: rgb(0,255,140);");
    }
    else
    {
        ui->dropTarget1->setStyleSheet("background-color: rgb(255,128,128);");
        ui->dropTarget2->setStyleSheet("background-color: rgb(255,128,128);");
    }
}
