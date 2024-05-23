#ifndef MESSAGEINFO_H
#define MESSAGEINFO_H

#include <QObject>
#include <QDateTime>

class Client;

class MessageInfo : public QObject
{
    Q_OBJECT
public:
    explicit MessageInfo(QObject *parent = nullptr);
    MessageInfo(Client *sender, const QString &text, const QDateTime &dateTime, QObject *parent = nullptr);

    Client* sender() const;
    QString text() const;
    QDateTime dateTime() const;

private:
    Client *m_sender;
    QString m_text;
    QDateTime m_dateTime;
};

#endif // MESSAGEINFO_H
