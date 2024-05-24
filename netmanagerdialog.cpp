#include "netmanagerdialog.h"
#include "ui_netmanagerdialog.h"

NetManagerDialog::NetManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetManagerDialog)
{
    ui->setupUi(this);
    onServerModeStateChanged();

    connect(ui->checkHost, &QCheckBox::stateChanged, this, &NetManagerDialog::onServerModeStateChanged);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &NetManagerDialog::onDialogAccepted);

    connect(ui->hostEdit, &QLineEdit::editingFinished, this, &NetManagerDialog::onValidateHost);
    connect(ui->portEdit, &QLineEdit::editingFinished, this, &NetManagerDialog::onValidatePort);
}

NetManagerDialog::~NetManagerDialog()
{
    delete ui;
}

void NetManagerDialog::onDialogAccepted()
{
    m_host = ui->hostEdit->text();
    m_port = ui->portEdit->text().toUShort();
    m_username = ui->usernameEdit->text();
    m_isServer = ui->checkHost->isChecked();
}

void NetManagerDialog::onServerModeStateChanged()
{
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    bool serverMode = ui->checkHost->isChecked();

    ui->hostEdit->setEnabled(!serverMode);

    if (okButton) {
        if (serverMode) {
            ui->usernameEdit->setText("server");
            okButton->setText("Host");
        }
        else {
            ui->usernameEdit->setText("usr1");
            okButton->setText("Connect");
        }
    }
}

void NetManagerDialog::onValidateHost()
{
    if (m_isServer)
        return;

    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);

    if (!isHostValid(ui->hostEdit->text())) {
        QMessageBox::warning(this, "Invalid IP", "The IP address is not valid.");

        okButton->setEnabled(false);
        return;
    } else {
        okButton->setEnabled(true);
    }
}

void NetManagerDialog::onValidatePort()
{
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);

    if (!ui->checkHost->isChecked()) {
        if (!isPortAvailable(ui->hostEdit->text(), ui->portEdit->text().toUShort())) {
            QMessageBox::warning(this, "Port Unavailable", "There are no listeners on this port.");
            okButton->setEnabled(false);
            return;
        }
    } else {
        if (!isPortFree(ui->portEdit->text().toUShort())) {
            QMessageBox::warning(this, "Port Unavailable", "The port is already in use.");
            okButton->setEnabled(false);
            return;
        }
    }
    okButton->setEnabled(true);
}

bool NetManagerDialog::isHostValid(const QString &ip)
{
    QHostAddress address;
    return address.setAddress(ip);
}

bool NetManagerDialog::isPortAvailable(const QString &ip, quint16 port)
{
    QTcpSocket socket;
    socket.connectToHost(ip, port);
    bool isConnected = socket.waitForConnected(10000);
    socket.disconnectFromHost();
    return isConnected;
}

bool NetManagerDialog::isPortFree(quint16 port)
{
    QTcpServer server;
    bool isFree = server.listen(QHostAddress::Any, port);
    server.close();
    return isFree;
}
