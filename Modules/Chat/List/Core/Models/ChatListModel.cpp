#include "ChatListModel.h"

ChatListModel::ChatListModel(QObject* parent) : QAbstractListModel(parent) {}

int ChatListModel::rowCount(const QModelIndex&) const { return m_items.size(); }

QVariant ChatListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_items.size()) return {};

    const auto& item = m_items.at(index.row());
    switch (role)
    {
        case TitleRole:
            return item.title;
        case LastMessageRole:
            return item.lastMessage;
        case AvatarRole:
            return item.avatar;
        case UnreadCountRole:
            return item.unreadCount;
    }
    return {};
}

void ChatListModel::addItem(const ChatListItem& item)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.append(item);
    endInsertRows();
}

void ChatListModel::clear()
{
    beginResetModel();
    m_items.clear();
    endResetModel();
}
