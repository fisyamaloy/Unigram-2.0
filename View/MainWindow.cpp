#include "MainWindow.h"
#include "Modules/Auth/AuthModule.h"
#include "Modules/Auth/Core/AuthFactory.h"
#include "Modules/Auth/AuthModuleFactory.h"
#include "Modules/Shared/Widgets/TitleBar.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QCursor>
#include <QGraphicsDropShadowEffect>
#include <QRect>
#include <qApplication>

const int RESIZE_MARGIN = 5;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), resizing(false)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    setMouseTracking(true);

    auto pLayout = new QVBoxLayout(this);
    pLayout->setContentsMargins(0, 0, 0, 0);

    pTitleBar = new TitleBarWidget(this);
    pLayout->addWidget(pTitleBar);

    AuthType selected = AuthType::LOGIN_PASSWORD;
    authModule = AuthModuleFactory::create(selected);
    auto pAuthForm = authModule.ui->widget();
    pLayout->addWidget(pAuthForm);

    if (authModule.strategy->authenticate())
    {
        // Authentification accepted
    }

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pAuthForm->setMouseTracking(true);
    pTitleBar->setMouseTracking(true);

    connect(pTitleBar, &TitleBarWidget::beginWindowMove, this, [this](const QPoint& globalPos) {
        if (!resizing) {
            m_dragOffset = globalPos - frameGeometry().topLeft();
            m_moving = true;
        }
    });

    connect(pTitleBar, &TitleBarWidget::windowMove, this, [this](const QPoint& globalPos) {
        if (m_moving && !resizing) {
            move(globalPos - m_dragOffset);
        }
    });
}

MainWindow::~MainWindow() {}

MainWindow::ResizeRegion MainWindow::getResizeRegion(const QPoint &pos)
{
    bool left = pos.x() <= RESIZE_MARGIN;
    bool right = pos.x() >= width() - RESIZE_MARGIN;
    bool top = pos.y() <= RESIZE_MARGIN;
    bool bottom = pos.y() >= height() - RESIZE_MARGIN;

    if (top && left)
        return TopLeft;
    if (top && right)
        return TopRight;
    if (bottom && left)
        return BottomLeft;
    if (bottom && right)
        return BottomRight;
    if (top)
        return Top;
    if (bottom)
        return Bottom;
    if (left)
        return Left;
    if (right)
        return Right;
    return None;
}

void MainWindow::updateCursorShape(const QPoint &pos)
{
    switch (getResizeRegion(pos))
    {
    case TopLeft:
    case BottomRight:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TopRight:
    case BottomLeft:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case Top:
    case Bottom:
        setCursor(Qt::SizeVerCursor);
        break;
    case Left:
    case Right:
        setCursor(Qt::SizeHorCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        resizeRegion = getResizeRegion(event->pos());
        if (resizeRegion != None)
        {
            resizing = true;
            dragStartPos = event->globalPosition().toPoint();
            originalGeometry = geometry();
        }
    }
}

static int i = 0;

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    static int eventCounter = 0;
    qDebug("MainWindow mouseMoveEvent %d", ++eventCounter);
    
    if (resizing)
    {
        const QPoint globalPos = event->globalPosition().toPoint();
        const QPoint delta = globalPos - dragStartPos;
        QRect newGeometry = originalGeometry;
        const QSize minSize = minimumSize();
        const QSize maxSize = maximumSize();

        auto validateWidth = [&]() {
            if (newGeometry.width() < minSize.width()) {
                if (resizeRegion == Left || resizeRegion == TopLeft || resizeRegion == BottomLeft) {
                    newGeometry.setLeft(newGeometry.right() - minSize.width());
                } else {
                    newGeometry.setRight(newGeometry.left() + minSize.width());
                }
            }
            else if (maxSize.width() > 0 && newGeometry.width() > maxSize.width()) {
                if (resizeRegion == Left || resizeRegion == TopLeft || resizeRegion == BottomLeft) {
                    newGeometry.setLeft(newGeometry.right() - maxSize.width());
                } else {
                    newGeometry.setRight(newGeometry.left() + maxSize.width());
                }
            }
        };

        auto validateHeight = [&]() {
            if (newGeometry.height() < minSize.height()) {
                if (resizeRegion == Top || resizeRegion == TopLeft || resizeRegion == TopRight) {
                    newGeometry.setTop(newGeometry.bottom() - minSize.height());
                } else {
                    newGeometry.setBottom(newGeometry.top() + minSize.height());
                }
            }
            else if (maxSize.height() > 0 && newGeometry.height() > maxSize.height()) {
                if (resizeRegion == Top || resizeRegion == TopLeft || resizeRegion == TopRight) {
                    newGeometry.setTop(newGeometry.bottom() - maxSize.height());
                } else {
                    newGeometry.setBottom(newGeometry.top() + maxSize.height());
                }
            }
        };

        switch (resizeRegion)
        {
        case Left:
            newGeometry.setLeft(originalGeometry.left() + delta.x());
            validateWidth();
            break;

        case Right:
            newGeometry.setRight(originalGeometry.right() + delta.x());
            validateWidth();
            break;

        case Top:
            newGeometry.setTop(originalGeometry.top() + delta.y());
            validateHeight();
            break;

        case Bottom:
            newGeometry.setBottom(originalGeometry.bottom() + delta.y());
            validateHeight();
            break;

        case TopLeft:
            newGeometry.setTopLeft(originalGeometry.topLeft() + delta);
            validateWidth();
            validateHeight();
            break;

        case TopRight:
            newGeometry.setTopRight(originalGeometry.topRight() + delta);
            validateWidth();
            validateHeight();
            break;

        case BottomLeft:
            newGeometry.setBottomLeft(originalGeometry.bottomLeft() + delta);
            validateWidth();
            validateHeight();
            break;

        case BottomRight:
            newGeometry.setBottomRight(originalGeometry.bottomRight() + delta);
            validateWidth();
            validateHeight();
            break;

        default:
            break;
        }

        const bool changed = (newGeometry != geometry());

        if (changed) {
            setGeometry(newGeometry);
            
            if (resizeRegion == Left || resizeRegion == TopLeft || resizeRegion == BottomLeft) {
                dragStartPos.setX(globalPos.x());
                originalGeometry.setLeft(newGeometry.left());
            }
            if (resizeRegion == Top || resizeRegion == TopLeft || resizeRegion == TopRight) {
                dragStartPos.setY(globalPos.y());
                originalGeometry.setTop(newGeometry.top());
            }
            if (resizeRegion == Right || resizeRegion == TopRight || resizeRegion == BottomRight) {
                originalGeometry.setRight(newGeometry.right());
            }
            if (resizeRegion == Bottom || resizeRegion == BottomLeft || resizeRegion == BottomRight) {
                originalGeometry.setBottom(newGeometry.bottom());
            }
        }

        QPoint localPos = mapFromGlobal(globalPos);
        updateCursorShape(localPos);
    }
    else
    {
        const QRect innerRect = rect().marginsRemoved(QMargins(RESIZE_MARGIN, RESIZE_MARGIN, RESIZE_MARGIN, RESIZE_MARGIN));
        if (!innerRect.contains(event->pos())) {
            updateCursorShape(event->pos());
        }
        else if (cursor().shape() != Qt::ArrowCursor) {
            setCursor(Qt::ArrowCursor);
        }
    }

    QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        resizing = false;
        m_moving = false;
        resizeRegion = None;
    }
    QWidget::mouseReleaseEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    updateCursorShape(mapFromGlobal(QCursor::pos()));
    QWidget::resizeEvent(event);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    if (getResizeRegion(event->position().toPoint()) == None)
    {
        if (isMaximized())
        {
            showNormal();
        }
        else
        {
            showMaximized();
        }
    }

    event->accept();
}

void MainWindow::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    // if (!resizing)
    // {
    //     setCursor(Qt::ArrowCursor);
    // }
}
