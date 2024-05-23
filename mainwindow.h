#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "netmanagerdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNetManagerOpenRequested();

private:
    Ui::MainWindow *ui;
    NetManagerDialog *m_netManagerDialog;
};
#endif // MAINWINDOW_H
