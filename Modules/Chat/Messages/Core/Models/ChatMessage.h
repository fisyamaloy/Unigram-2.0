#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H

#include <QPixmap>
#include <QString>

struct ChatMessage
{
    QString sender;
    QString text;
    QString time;
    QPixmap avatar;
};

#endif  // !CHAT_MESSAGE_H
