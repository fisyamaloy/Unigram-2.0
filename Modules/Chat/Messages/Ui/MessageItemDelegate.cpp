#include "MessageItemDelegate.h"

#include <Chat/Messages/Core/Models/MessageListModel.h>

#include <QPainter>
#include <QTextLayout>
#include <QTextOption>

MessageItemDelegate::MessageItemDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

void MessageItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    static constexpr int padding = 10;
    static constexpr int avatarSize = 40;
    static constexpr int spacing = 6;

    painter->save();

    QRect rect = option.rect;
    painter->setRenderHint(QPainter::Antialiasing);

    // Данные
    QString sender  = index.data(MessageListModel::SenderRole).toString();
    QString message = index.data(MessageListModel::TextRole).toString();
    QString time    = index.data(MessageListModel::TimeRole).toString();
    QPixmap avatar  = index.data(MessageListModel::AvatarRole).value<QPixmap>().scaled(avatarSize, avatarSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Фон баббла
    QRect bubbleRect = rect.adjusted(padding, padding / 2, -padding, -padding / 2);
    painter->setBrush(QColor("#2a2d32"));
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(bubbleRect, 10, 10);

    // Шрифты и метрики
    QFont senderFont = option.font;
    senderFont.setBold(true);
    QFontMetrics senderMetrics(senderFont);

    QFont messageFont = option.font;
    QFontMetrics messageMetrics(messageFont);

    QFont timeFont = option.font;
    //timeFont.setPointSize(timeFont.pointSize() - 1);
    QFontMetrics timeMetrics(timeFont);
    int timeWidth = timeMetrics.horizontalAdvance(time);

    // Подготовка текстового layout
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    QTextLayout textLayout(message, messageFont);
    textLayout.setTextOption(textOption);
    textLayout.beginLayout();

    QVector<QTextLine> lines;
    int totalTextHeight = 0;
    int textWidth = bubbleRect.width() - 3 * padding - avatarSize - timeWidth;

    while (true) {
        QTextLine line = textLayout.createLine();
        if (!line.isValid())
            break;
        line.setLineWidth(textWidth);
        totalTextHeight += line.height();
        lines.append(line);
    }

    textLayout.endLayout();

    // Общая высота текстовой части
    int contentHeight = senderMetrics.height() + spacing + totalTextHeight;

    // Координаты X
    int textX = bubbleRect.left() + padding + avatarSize + spacing;
    int textY = bubbleRect.top() + (bubbleRect.height() - contentHeight) / 2;

    // Координаты аватарки — по центру текста
    int avatarX = bubbleRect.left() + padding;
    int avatarY = textY + (contentHeight - avatarSize) / 2;

    // Аватарка
    painter->drawPixmap(avatarX, avatarY, avatarSize, avatarSize, avatar);

    // Имя
    painter->setFont(senderFont);
    painter->setPen(QColor("#43b581"));
    painter->drawText(textX, textY + senderMetrics.ascent(), sender);

    // Сообщение
    painter->setFont(messageFont);
    painter->setPen(Qt::white);
    int msgY = textY + senderMetrics.height() + spacing;
    QPoint basePoint(textX, msgY);

    for (int i = 0; i < lines.size(); ++i) {
        lines[i].setPosition(QPointF(basePoint));
        lines[i].draw(painter, QPoint(0, 0));
        basePoint.ry() += lines[i].height();
    }

    // Время
    painter->setFont(timeFont);
    painter->setPen(QColor("#888"));
    int timeX = bubbleRect.right() - padding - timeWidth;
    int timeY = msgY + totalTextHeight - timeMetrics.descent();
    painter->drawText(timeX, timeY, time);

    painter->restore();
}

QSize MessageItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    static constexpr int padding = 10;
    static constexpr int avatarSize = 40;
    static constexpr int spacing = 6;

    // Данные
    QString sender  = index.data(MessageListModel::SenderRole).toString();
    QString message = index.data(MessageListModel::TextRole).toString();
    QString time    = index.data(MessageListModel::TimeRole).toString();

    // Шрифты и метрики
    QFont senderFont = option.font;
    senderFont.setBold(true);
    QFontMetrics senderMetrics(senderFont);

    QFont messageFont = option.font;
    QFontMetrics messageMetrics(messageFont);

    QFont timeFont = option.font;
    //timeFont.setPointSize(timeFont.pointSize() - 1);
    QFontMetrics timeMetrics(timeFont);
    int timeWidth = timeMetrics.horizontalAdvance(time);

    // Подготовка текстового layout
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    QTextLayout textLayout(message, messageFont);
    textLayout.setTextOption(textOption);
    textLayout.beginLayout();

    int textWidth = 600 - 3 * padding - avatarSize - timeWidth; // предполагаемая ширина
    int totalTextHeight = 0;

    while (true) {
        QTextLine line = textLayout.createLine();
        if (!line.isValid())
            break;
        line.setLineWidth(textWidth);
        totalTextHeight += line.height();
    }

    textLayout.endLayout();

    // Итоговая высота: имя + отступ + сообщение + внешние паддинги
    int contentHeight = senderMetrics.height() + spacing + totalTextHeight;
    int finalHeight = std::max(avatarSize, contentHeight) + padding;

    return QSize(0, finalHeight);
}
