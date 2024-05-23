#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNetworkManage, &QAction::triggered, this, &MainWindow::onNetManagerOpenRequested);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNetManagerOpenRequested()
{
    m_netManagerDialog = new NetManagerDialog();

    if (m_netManagerDialog->exec() != QDialog::Accepted) {
        return;
    }
}

