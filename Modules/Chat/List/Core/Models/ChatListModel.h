#ifndef CHAT_LIST_MODEL_H

#include <QAbstractListModel>
#include "ChatListItem.h"

class ChatListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles {
        TitleRole = Qt::UserRole + 1,
        LastMessageRole,
        AvatarRole,
        UnreadCountRole
    };

    ChatListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    void addItem(const ChatListItem& item);
    void clear();

private:
    QList<ChatListItem> m_items;
};

#endif //!CHAT_LIST_MODEL_H
