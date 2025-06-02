#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>

class MessageListWidget;

class ChatPage : public QWidget
{
    Q_OBJECT
public:
    ChatPage(QWidget* parent = nullptr);

private:
    constexpr static const char* kChatPlaceholderText = "Select a chat to start messaging";
    //QMap<int, MessageListWidget*> chatViews;
};

#endif // !CHATPAGE_H
