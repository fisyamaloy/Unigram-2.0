#include "MessageListModel.h"

MessageListModel::MessageListModel(QObject* parent) : QAbstractListModel(parent) {}

int MessageListModel::rowCount(const QModelIndex&) const { return m_messages.size(); }

QVariant MessageListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_messages.size()) return {};

    const ChatMessage& msg = m_messages.at(index.row());
    switch (role)
    {
        case SenderRole:
            return msg.sender;
        case TextRole:
            return msg.text;
        case TimeRole:
            return msg.time;
        case AvatarRole:
            return msg.avatar;
    }
    return {};
}

void MessageListModel::addMessage(const ChatMessage& message)
{
    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
    m_messages.append(message);
    endInsertRows();
}

void MessageListModel::clear()
{
    beginResetModel();
    m_messages.clear();
    endResetModel();
}
