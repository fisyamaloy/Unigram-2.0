#include "ChatListWidget.h"
#include "ChatItemDelegate.h"

ChatListWidget::ChatListWidget(QWidget* parent) : QListView(parent)
{
    setItemDelegate(new ChatItemDelegate(this));
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}
