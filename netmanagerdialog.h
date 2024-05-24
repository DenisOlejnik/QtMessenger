#ifndef NETMANAGERDIALOG_H
#define NETMANAGERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QMessageBox>

namespace Ui {
class NetManagerDialog;
}

class NetManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetManagerDialog(QWidget *parent = nullptr);
    ~NetManagerDialog();

    QString host() const { return m_host; }
    quint16 port() const { return m_port; }
    QString username() const { return m_username; }
    bool isServer() const { return m_isServer; }

private slots:
    void onDialogAccepted();
    void onServerModeStateChanged();
    void onValidateHost();
    void onValidatePort();

private:
    bool isHostValid(const QString &ip);
    bool isPortAvailable(const QString &ip, quint16 port);
    bool isPortFree(quint16 port);

private:
    Ui::NetManagerDialog *ui;
    QString m_host;
    quint16 m_port;
    QString m_username;
    bool m_isServer;
};

#endif // NETMANAGERDIALOG_H
