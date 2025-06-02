#include "MessageListWidget.h"

#include <Chat/Messages/Core/Models/MessageListModel.h>

#include "MessageItemDelegate.h"

#include <QMouseEvent>
#include <QApplication>
#include <QPushButton>

MessageListWidget::MessageListWidget(QWidget* parent) : QListView(parent), model(new MessageListModel(this))
{
    setModel(model);
    setItemDelegate(new MessageItemDelegate(this));
    setStyleSheet("QListView { background-color: #1e1e1e; border: none; }");
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MessageListWidget::addMessage(const ChatMessage& msg)
{
    model->addMessage(msg);
    scrollToBottom();
}

void MessageListWidget::clearMessages() { model->clear(); }

void MessageListWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (auto* mainWin = parentWidget()) {
        QCoreApplication::sendEvent(mainWin, event);
    }

    QListView::mouseMoveEvent(event);
}
