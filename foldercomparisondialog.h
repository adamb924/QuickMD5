#ifndef FOLDERCOMPARISONDIALOG_H
#define FOLDERCOMPARISONDIALOG_H

#include <QDialog>

namespace Ui {
    class FolderComparisonDialog;
}

class FolderComparisonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FolderComparisonDialog(const QString & one, const QString & two, QWidget *parent = 0);
    ~FolderComparisonDialog();

    void addRow( const QString & file , const QString & hashOne , const QString & hashTwo );

private:
    Ui::FolderComparisonDialog *ui;
};

#endif // FOLDERCOMPARISONDIALOG_H
