#include "foldercomparisondialog.h"
#include "ui_foldercomparisondialog.h"

FolderComparisonDialog::FolderComparisonDialog(const QString & one, const QString & two, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FolderComparisonDialog)
{
    ui->setupUi(this);

    ui->tableWidget->setHorizontalHeaderLabels( QStringList() << tr("File") << tr("First hash") << tr("Second hash") );

    ui->label1->setText(one);
    ui->label2->setText(two);
}

FolderComparisonDialog::~FolderComparisonDialog()
{
    delete ui;
}

void FolderComparisonDialog::addRow( const QString & file , const QString & hashOne , const QString & hashTwo )
{
    int i = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow( i );

    ui->tableWidget->setItem( i, 0 , new QTableWidgetItem( file ) );
    ui->tableWidget->setItem( i, 1 , new QTableWidgetItem( hashOne ) );
    ui->tableWidget->setItem( i, 2 , new QTableWidgetItem( hashTwo ) );

    QColor color = hashOne == hashTwo ? QColor(0,255,140) :  QColor(255,128,128);
    ui->tableWidget->item(i,0)->setBackgroundColor(color);
    ui->tableWidget->item(i,1)->setBackgroundColor(color);
    ui->tableWidget->item(i,2)->setBackgroundColor(color);
}
