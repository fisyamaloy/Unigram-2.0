#ifndef CHAT_LIST_ITEM_H

#include <QPixmap>
#include <QString>

struct ChatListItem
{
    QString title;
    QString lastMessage;
    QPixmap avatar;
    int     unreadCount = 0;
};

#endif  //! CHAT_LIST_ITEM_H
