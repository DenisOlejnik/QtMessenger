#ifndef NETMANAGERDIALOG_H
#define NETMANAGERDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class NetManagerDialog;
}

class NetManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetManagerDialog(QWidget *parent = nullptr);
    ~NetManagerDialog();

private slots:
    void onDialogAccepted();
    void onServerModeStateChanged();

private:
    Ui::NetManagerDialog *ui;
};

#endif // NETMANAGERDIALOG_H
