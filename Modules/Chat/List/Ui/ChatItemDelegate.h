#ifndef CHAT_ITEM_DELEGATE_H
#include <QStyledItemDelegate>

class ChatItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    void  paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif  //! CHAT_ITEM_DELEGATE_H
