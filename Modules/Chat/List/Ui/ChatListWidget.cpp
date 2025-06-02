#include "ChatListWidget.h"

#include <QModelIndex>

#include "ChatItemDelegate.h"

ChatListWidget::ChatListWidget(QWidget* parent) : QListView(parent)
{
    setItemDelegate(new ChatItemDelegate(this));
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setMouseTracking(true);
    installEventFilter(this);

    connect(this, &QAbstractItemView::entered, [this](const QModelIndex& index) {
        if (index.isValid())
        {
            setCursor(Qt::PointingHandCursor);
        }
    });

    connect(this, &QAbstractItemView::viewportEntered, [this]() {
        unsetCursor();
    });
}
