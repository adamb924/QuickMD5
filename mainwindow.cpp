#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DropFilenameLineEdit.h"
#include "hash.h"
#include "foldercomparisondialog.h"

#include <QDir>
#include <QTableWidget>
#include <QtDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("QuickMD5"));

    connect( ui->dropTarget1, SIGNAL(textChanged(QString)), this, SLOT(hashChanged()));
    connect( ui->dropTarget2, SIGNAL(textChanged(QString)), this, SLOT(hashChanged()));

    connect( ui->dropTarget1, SIGNAL(filenameChanged(QString)), ui->label1, SLOT(setText(QString)) );
    connect( ui->dropTarget2, SIGNAL(filenameChanged(QString)), ui->label2, SLOT(setText(QString)) );

    connect( ui->dropTarget1, SIGNAL(filenameChanged(QString)), this, SLOT(doFolderComparison()));
    connect( ui->dropTarget2, SIGNAL(filenameChanged(QString)), this, SLOT(doFolderComparison()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hashChanged()
{
    const bool theSame = ui->dropTarget1->text() == ui->dropTarget2->text();
    const QString green = "background-color: rgb(0,255,140);";
    const QString red = "background-color: rgb(255,128,128);";
    ui->dropTarget1->setStyleSheet( theSame ? green : red );
    ui->dropTarget2->setStyleSheet( theSame ? green : red );
}

void MainWindow::doFolderComparison()
{
    QDir one( ui->label1->text() );
    QDir two( ui->label2->text() );
    if( !one.exists() || !two.exists() )
        return;

    one.setFilter(QDir::Files);
    one.setNameFilters(QStringList("*.*"));
    one.setSorting(QDir::Name);
    QStringList listOne = one.entryList(QDir::Files,QDir::Name);

    two.setFilter(QDir::Files);
    two.setNameFilters(QStringList("*.*"));
    two.setSorting(QDir::Name);
    QStringList listTwo = two.entryList(QDir::Files,QDir::Name);

    FolderComparisonDialog * dialog = new FolderComparisonDialog(ui->label1->text(), ui->label2->text(), this);

    bool hasCommonFiles = false;
    for(int i=0; i<listOne.count(); i++)
        if( listTwo.contains( listOne.at(i) ) )
        {
            dialog->addRow( listOne.at(i) , fileHash( one.absoluteFilePath(listOne.at(i))) , fileHash( two.absoluteFilePath(listOne.at(i))) );
            hasCommonFiles = true;
        }

    if( hasCommonFiles )
        dialog->show();
    else
        QMessageBox::information(this, tr("No comparison to make"), tr("There are no file names in common between these folders."));
}
