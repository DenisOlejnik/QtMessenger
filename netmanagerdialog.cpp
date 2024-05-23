#include "netmanagerdialog.h"
#include "ui_netmanagerdialog.h"

NetManagerDialog::NetManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetManagerDialog)
{
    ui->setupUi(this);
    onServerModeStateChanged();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &NetManagerDialog::onDialogAccepted);
    connect(ui->checkHost, &QCheckBox::stateChanged, this, &NetManagerDialog::onServerModeStateChanged);
}

NetManagerDialog::~NetManagerDialog()
{
    delete ui;
}

void NetManagerDialog::onDialogAccepted()
{
    qDebug () << "accepted";
}

void NetManagerDialog::onServerModeStateChanged()
{
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    bool serverMode = ui->checkHost->isChecked();

    ui->hostEdit->setEnabled(!serverMode);

    if (okButton) {
        if (serverMode) {
            okButton->setText("Host");
        }
        else {
            okButton->setText("Connect");
        }
    }
}
