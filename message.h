#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include "messageinfo.h"

namespace Ui {
class Message;
}

class Message : public QWidget
{
    Q_OBJECT

public:
    explicit Message(const MessageInfo &msgInfo, bool isOwnMessage, QWidget *parent = nullptr);
    ~Message();

private:
    Ui::Message *ui;
};

#endif // MESSAGE_H
