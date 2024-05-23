#include "messageinfo.h"

MessageInfo::MessageInfo(QObject *parent)
    : QObject{parent}, m_sender(nullptr), m_text(""), m_dateTime(QDateTime::currentDateTime())
{

}

MessageInfo::MessageInfo(Client *sender, const QString &text, const QDateTime &dateTime, QObject *parent)
    : QObject{parent}, m_sender(sender), m_text(text), m_dateTime(dateTime)
{

}

Client *MessageInfo::sender() const
{
    return m_sender;
}

QString MessageInfo::text() const
{
    return m_text;
}

QDateTime MessageInfo::dateTime() const
{
    return m_dateTime;
}
