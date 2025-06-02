#include "AutoGrowingTextEdit.h"

#include <QFontMetrics>

AutoGrowingTextEdit::AutoGrowingTextEdit(QWidget* parent) : QTextEdit(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    connect(this, &QTextEdit::textChanged, this, &AutoGrowingTextEdit::updateHeight);
    updateHeight();
}

void AutoGrowingTextEdit::resizeEvent(QResizeEvent* event)
{
    QTextEdit::resizeEvent(event);
    updateHeight();
}

// QSize AutoGrowingTextEdit::sizeHint() const
// {
//     QSize s         = QTextEdit::sizeHint();
//     int   docHeight = document()->size().height();
//     int   h         = qBound(MINIMUN_HEIGHT, static_cast<int>(docHeight + 10), MAXIMUM_HEIGHT);
//     return QSize(s.width(), h);
// }

void AutoGrowingTextEdit::updateHeight()
{
    document()->setTextWidth(viewport()->width());
    QSize     docSize   = document()->size().toSize();
    const int newHeight = qMin(MAXIMUM_HEIGHT, docSize.height() + 8);
    setMinimumHeight(newHeight);
    setMaximumHeight(newHeight);
}
