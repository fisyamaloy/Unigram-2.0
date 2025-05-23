#include "ChatItemDelegate.h"

#include "../Core/Models/ChatListModel.h"

#include <QApplication>
#include <QStyle>
#include <QPainter>

void ChatItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();
    QRect rect = option.rect;

    QStyle* style = QApplication::style();
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &option, painter);

    QColor titleColor    = option.palette.color(QPalette::Text);
    QColor subtitleColor = option.palette.color(QPalette::Mid);

    QPixmap avatar = index.data(ChatListModel::AvatarRole).value<QPixmap>().scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(rect.left() + 10, rect.top() + 10, avatar);

    int x = rect.left() + 60;
    int y = rect.top() + 10;

    QString title = index.data(ChatListModel::TitleRole).toString();
    painter->setPen(titleColor);
    QFont boldFont = option.font;
    boldFont.setBold(true);
    painter->setFont(boldFont);
    painter->drawText(x, y + 15, title);

    QString msg = index.data(ChatListModel::LastMessageRole).toString();
    painter->setPen(subtitleColor);
    painter->setFont(option.font);
    painter->drawText(x, y + 35, msg);

    int count = index.data(ChatListModel::UnreadCountRole).toInt();
    if (count > 0)
    {
        QRect badgeRect(rect.right() - 30, rect.top() + 20, 20, 20);
        painter->setBrush(QColor("#d63c3c"));
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(badgeRect);
        painter->setPen(Qt::white);
        painter->drawText(badgeRect, Qt::AlignCenter, QString::number(count));
    }

    painter->restore();
}

QSize ChatItemDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const { return QSize(200, 60); }
