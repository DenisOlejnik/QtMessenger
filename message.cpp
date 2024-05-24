#include "message.h"
#include "ui_message.h"

Message::Message(const MessageInfo &msgInfo, bool isOwnMessage, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Message)
{
    ui->setupUi(this);
    ui->usernameLabel->setText(msgInfo.sender());
    ui->messageLabel->setText(msgInfo.text());
    ui->timeLabel->setText(msgInfo.dateTime().toString("hh:mm:ss"));

    if (isOwnMessage) {
        ui->spacerRight->changeSize(0, 0, QSizePolicy::Ignored);
        setStyleSheet(styleSheet() + " background-color: lightblue; color: black; ");
        ui->horizontalLayout->setStretch(0, 2);
        ui->horizontalLayout->setStretch(1, 3);
    }
    else {
        ui->spacerLeft->changeSize(0, 0, QSizePolicy::Ignored);
        setStyleSheet(styleSheet() + " background-color: lightgray; color: black; ");
        ui->horizontalLayout->setStretch(1, 3);
        ui->horizontalLayout->setStretch(2, 2);
    }

}

Message::~Message()
{
    delete ui;
}
