#ifndef MESSAGE_LIST_MODEL_H
#define MESSAGE_LIST_MODEL_H

#include "ChatMessage.h"

#include <QAbstractListModel>
#include <QList>

class MessageListModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        SenderRole = Qt::UserRole + 1,
        TextRole,
        TimeRole,
        AvatarRole
    };

    MessageListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    void addMessage(const ChatMessage& message);
    void clear();

private:
    QList<ChatMessage> m_messages;
};

#endif // !MESSAGE_LIST_MODEL_H
