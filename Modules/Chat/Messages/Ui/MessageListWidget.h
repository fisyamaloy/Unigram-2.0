#ifndef MESSAGE_LIST_WIDGET_H
#define MESSAGE_LIST_WIDGET_H

#include <QListView>
#include <Chat/Messages/Core/Models/ChatMessage.h>

class MessageListModel;
class QPushButton;

class MessageListWidget : public QListView {
    Q_OBJECT

public:
    MessageListWidget(QWidget* parent = nullptr);

    void addMessage(const ChatMessage& msg);
    void clearMessages();

protected:
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    MessageListModel* model;
};

#endif // !MESSAGE_LIST_WIDGET_H
