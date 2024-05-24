#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "message.h"
#include "messageinfo.h"
#include "netmanagerdialog.h"
#include "client.h"
#include "server.h"

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
    void onBtnSendClicked();
    void updateChatMessages(const MessageInfo &newMessage);

private:
    Ui::MainWindow *ui;
    QVBoxLayout *m_scrollLayout;

    NetManagerDialog *m_netManagerDialog = nullptr;
    Server *m_server = nullptr;
    Client *m_client = nullptr;
};
#endif // MAINWINDOW_H
