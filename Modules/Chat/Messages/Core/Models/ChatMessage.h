#ifndef CHAT_MESSAGE_H

#include <QDateTime>
#include <QPixmap>
#include <QString>

struct ChatMessage
{
    QString   sender;
    QString   lastMessage;
    QDateTime timestamp;
    int       unreadCount;
    QPixmap   avatar;
};

#endif  // !CHAT_MESSAGE_H
