#ifndef MESSAGEINFO_H
#define MESSAGEINFO_H

#include <QObject>
#include <QDateTime>

class MessageInfo : public QObject
{
    Q_OBJECT
public:
    MessageInfo(QObject *parent = nullptr);
    MessageInfo(const QString &sender, const QString &text, const QDateTime &dateTime = QDateTime::currentDateTime(), QObject *parent = nullptr);
    MessageInfo(bool isService, const QString &text, QObject *parent = nullptr);

    QString sender() const { return m_sender; }
    QString text() const { return m_text; }
    QDateTime dateTime() const { return m_dateTime; }
    bool isServiceMsg() const { return m_isService;}

    friend QDataStream &operator<<(QDataStream &out, const MessageInfo &message);
    friend QDataStream &operator>>(QDataStream &in, MessageInfo &message);

private:
    QString m_sender = nullptr;
    QString m_text = nullptr;
    QDateTime m_dateTime = QDateTime();
    bool m_isService = false;
};

#endif // MESSAGEINFO_H
