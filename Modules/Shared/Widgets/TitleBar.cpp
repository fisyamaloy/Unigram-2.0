#include "TitleBar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QApplication>
#include <QWindow>
#include <QPainter>
#include <QStyle>

TitleBarWidget::TitleBarWidget(QWidget* parent)
    : QFrame(parent)
{
    setObjectName("TitleBarWidget");
    setFixedHeight(36);
        
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);

    setAutoFillBackground(true);
    setStyleSheet("background-color:rgb(177, 77, 77); border-bottom: 1px solid red;");

    auto* layout = new QHBoxLayout;
    layout->setContentsMargins(8, 0, 8, 0);

    //auto* title = new QLabel("My Frameless App", this);
    //layout->addWidget(title);
    layout->addStretch();

    auto* btnMin = new QPushButton("-", this);
    auto* btnClose = new QPushButton("X", this);

    btnMin->setFixedSize(36, 36);
    btnClose->setFixedSize(36, 36);
    layout->addWidget(btnMin);
    layout->addWidget(btnClose);

    setLayout(layout);

    connect(btnMin, &QPushButton::clicked, this, [] {
        QWidget* w = QApplication::activeWindow();
        if (w) w->showMinimized();
    });

    connect(btnClose, &QPushButton::clicked, this, [] {
        QApplication::quit();
    });
}

void TitleBarWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPosition().toPoint() - parentWidget()->frameGeometry().topLeft();
        event->accept();
        //grabMouse();
    }
    qDebug() << "TitleBar mousePressEvent\n";
    QFrame::mousePressEvent(event);
}

void TitleBarWidget::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        parentWidget()->move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
    qDebug() << "TitleBar mouseMoveEvent\n";
    QFrame::mouseMoveEvent(event);
}

void TitleBarWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (event->button() == Qt::LeftButton) {
        event->accept();
        //releaseMouse();
    }

    qDebug() << "TitleBar mouseReleaseEvent\n";
    QFrame::mouseReleaseEvent(event);
}
