#ifndef CHAT_CONVERSATION_AREA_H
#define CHAT_CONVERSATION_AREA_H

#include <QMap>
#include <QWidget>

class MessageListWidget;
class AutoGrowingTextEdit;
class QPushButton;
class QStackedLayout;

class ChatConversationArea : public QWidget
{
    Q_OBJECT

public:
    explicit ChatConversationArea(QWidget* parent = nullptr);

    void showChatForRow(int row, const QString& chatTitle);

private slots:
    void onSendClicked();

private:
    QStackedLayout*               m_chatStack;
    QMap<int, MessageListWidget*> m_chatWidgets;

    AutoGrowingTextEdit* m_inputEdit;
    QPushButton*         m_sendButton;
};

#endif  // !CHAT_CONVERSATION_AREA_H
