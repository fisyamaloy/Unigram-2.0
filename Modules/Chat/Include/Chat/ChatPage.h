#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>

class ChatPage : public QWidget
{
    Q_OBJECT
public:
    ChatPage(QWidget* parent = nullptr);

private:
    constexpr static const char* kChatPlaceholderText = "Select a chat to start messaging";
};

#endif // !CHATPAGE_H
