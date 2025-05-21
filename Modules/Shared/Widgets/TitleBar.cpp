#include "TitleBar.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QStyle>
#include <QWindow>

TitleBarWidget::TitleBarWidget(QWidget* parent) : QFrame(parent)
{
    this->setMouseTracking(true);

    setObjectName("TitleBarWidget");
    setFixedHeight(36);

    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);

    // setStyleSheet("background-color:rgb(177, 77, 77); border-bottom: 1px solid red;");

    auto* layout = new QHBoxLayout;
    layout->setContentsMargins(8, 0, 8, 0);

    // auto* title = new QLabel("My Frameless App", this);
    // layout->addWidget(title);
    layout->addStretch();

    auto* btnMin   = new QPushButton("-", this);
    auto* btnMax   = new QPushButton("[]", this);
    auto* btnClose = new QPushButton("x", this);

    btnMin->setFocusPolicy(Qt::NoFocus);
    btnMax->setFocusPolicy(Qt::NoFocus);
    btnClose->setFocusPolicy(Qt::NoFocus);
    btnMin->setFixedSize(36, 36);
    btnMax->setFixedSize(36, 36);
    btnClose->setFixedSize(36, 36);

    layout->addWidget(btnMin);
    layout->addWidget(btnMax);
    layout->addWidget(btnClose);

    setLayout(layout);

    connect(btnMin, &QPushButton::clicked, this, [] {
        QWidget* w = QApplication::activeWindow();
        if (w) w->showMinimized();
    });

    connect(btnMax, &QPushButton::clicked, this, [] {
        QWidget* w = QApplication::activeWindow();
        if (w)
        {
            if (w->isMaximized())
                w->showNormal();
            else
                w->showMaximized();
        }
    });

    connect(btnClose, &QPushButton::clicked, this, [] { QApplication::quit(); });
}

void TitleBarWidget::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "TitleBar mousePressEvent\n";

    if (event->button() == Qt::LeftButton)
    {
        m_dragPosition = event->globalPosition().toPoint();
        emit beginWindowMove(m_dragPosition);
        event->accept();
    }
    QFrame::mousePressEvent(event);
}

void TitleBarWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        emit windowMove(event->globalPosition().toPoint());
        event->accept();
    }
    QFrame::mouseMoveEvent(event);
}

void TitleBarWidget::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << "TitleBar mouseReleaseEvent\n";

    if (event->button() == Qt::LeftButton)
    {
        event->accept();
    }
    QFrame::mouseReleaseEvent(event);
}
