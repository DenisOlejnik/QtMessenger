#ifndef NEWMANAGERDIALOG_H
#define NEWMANAGERDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class NewManagerDialog;
}

class NewManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewManagerDialog(QWidget *parent = nullptr);
    ~NewManagerDialog();

private slots:
    void onDialogAccepted();
    void onServerModeStateChanged();

private:
    Ui::NewManagerDialog *ui;
};

#endif // NEWMANAGERDIALOG_H
