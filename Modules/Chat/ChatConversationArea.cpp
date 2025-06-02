#include "Chat/ChatConversationArea.h"

#include <Shared/Widgets/AutoGrowingTextEdit.h>

#include "Messages/Core/Models/ChatMessage.h"
#include "Messages/Ui/MessageListWidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedLayout>
#include <QTime>
#include <QVBoxLayout>

ChatConversationArea::ChatConversationArea(QWidget* parent) : QWidget(parent)
{
    m_chatStack  = new QStackedLayout;
    m_inputEdit  = new AutoGrowingTextEdit(this);
    m_sendButton = new QPushButton("Send", this);

    m_inputEdit->setPlaceholderText("Write a message...");
    m_inputEdit->setMinimumHeight(50);
    m_sendButton->setFixedWidth(80);    
    m_sendButton->setFocusPolicy(Qt::NoFocus);

    m_inputEdit->hide();
    m_sendButton->hide();

    QHBoxLayout* inputLayout = new QHBoxLayout;
    inputLayout->addWidget(m_inputEdit);
    inputLayout->addWidget(m_sendButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(m_chatStack);
    mainLayout->addLayout(inputLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(6);

    connect(m_sendButton, &QPushButton::clicked, this, &ChatConversationArea::onSendClicked);
    // connect(m_inputEdit, &QLineEdit::returnPressed, this, &ChatConversationArea::onSendClicked);
}

void ChatConversationArea::showChatForRow(int row, const QString& chatTitle)
{
    if (!m_chatWidgets.contains(row))
    {
        auto* pChatView    = new MessageListWidget(this);
        m_chatWidgets[row] = pChatView;
        m_chatStack->addWidget(pChatView);

        // Add welcome/test message
        ChatMessage msg;
        msg.sender = chatTitle;
        msg.text   = "Привет! Это чат с " + chatTitle;
        msg.time   = QTime::currentTime().toString("HH:mm");
        msg.avatar = QPixmap(":/icons/not_found.png");

        for (int i = 0; i < 10; ++i)
            pChatView->addMessage({chatTitle,
                                   "Привет! Это тестовое сообщение. аывапывап ывап ывап ывап ывап ывапыавпржы валюпрд ывардп ывдарп ыдва "
                                   "поыывапывапывапывапывапывапдырвадпыварпдывапдывапдыважррфывж фыжва рфыжва рфыва фжыва 2345 346 345 "
                                   "634563456цуа ывап ывапывап уке234534е уапуапуарпарвапрпар",
                                   "14:55",
                                   QPixmap(":/icons/not_found.png")});

        pChatView->addMessage(msg);

        pChatView->setMouseTracking(true);
        pChatView->installEventFilter(this);
        pChatView->viewport()->setMouseTracking(true);
        pChatView->viewport()->installEventFilter(this);
    }

    if (m_inputEdit->isHidden())
    {
        m_inputEdit->show();
    }
    if (m_sendButton->isHidden())
    {
        m_sendButton->show();
    }

    m_chatStack->setCurrentWidget(m_chatWidgets[row]);
}

void ChatConversationArea::onSendClicked()
{
    const QString text = m_inputEdit->toPlainText().trimmed();
    if (text.isEmpty())
    {
        return;
    }

    auto* currentChat = qobject_cast<MessageListWidget*>(m_chatStack->currentWidget());
    if (!currentChat) 
    {
        return;
    }

    ChatMessage msg;
    msg.sender = "Me";
    msg.text   = text;
    msg.time   = QTime::currentTime().toString("HH:mm");

    currentChat->addMessage(msg);

    m_inputEdit->clear();
}
