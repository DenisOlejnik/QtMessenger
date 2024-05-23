#include "newmanagerdialog.h"
#include "ui_newmanagerdialog.h"

NewManagerDialog::NewManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewManagerDialog)
{
    ui->setupUi(this);
    onServerModeStateChanged();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &NewManagerDialog::onDialogAccepted);
    connect(ui->checkHost, &QCheckBox::stateChanged, this, &NewManagerDialog::onServerModeStateChanged);
}

NewManagerDialog::~NewManagerDialog()
{
    delete ui;
}

void NewManagerDialog::onDialogAccepted()
{
    qDebug () << "accepted";
}

void NewManagerDialog::onServerModeStateChanged()
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
