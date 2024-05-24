#include "messageinfo.h"

MessageInfo::MessageInfo(QObject *parent)
    : QObject{parent}
{

}

MessageInfo::MessageInfo(const QString &sender, const QString &text, const QDateTime &dateTime, QObject *parent)
    : QObject{parent},
      m_sender(sender),
      m_text(text),
      m_dateTime(dateTime)
{

}

MessageInfo::MessageInfo(bool isService, const QString &text, QObject *parent)
    : QObject{parent},
      m_isService(isService),
      m_text(text)
{

}

QDataStream &operator<<(QDataStream &out, const MessageInfo &message) {
    out << message.m_sender << message.m_text << message.m_dateTime << message.m_isService;

    return out;
}

QDataStream &operator>>(QDataStream &in, MessageInfo &message) {
    in >> message.m_sender >> message.m_text >> message.m_dateTime >> message.m_isService;

    return in;
}
