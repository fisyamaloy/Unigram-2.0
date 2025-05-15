#include "MainWindow.h"
#include "Modules/Auth/AuthModule.h"
#include "Modules/Auth/Core/AuthFactory.h"
#include "Modules/Auth/AuthModuleFactory.h"
#include "Modules/Shared/Widgets/TitleBar.h"

#include <QVBoxLayout>
#include <QMouseEvent>
#include <QCursor>
#include <QWindow>

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

    if (authModule.strategy->authenticate()) {
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

    if (top && left) return TopLeft;
    if (top && right) return TopRight;
    if (bottom && left) return BottomLeft;
    if (bottom && right) return BottomRight;
    if (top) return Top;
    if (bottom) return Bottom;
    if (left) return Left;
    if (right) return Right;
    return None;
}

void MainWindow::updateCursorShape(const QPoint &globalPos)
{
    QPoint localPos = mapFromGlobal(globalPos);
    const auto region = getResizeRegion(localPos);

    Qt::CursorShape shape = Qt::ArrowCursor;

    switch (region)
    {
        case Left:
        case Right:
            shape = Qt::SizeHorCursor;
            break;

        case Top:
        case Bottom:
            shape = Qt::SizeVerCursor;
            break;

        case TopLeft:
        case BottomRight:
            shape = Qt::SizeFDiagCursor;
            break;

        case TopRight:
        case BottomLeft:
            shape = Qt::SizeBDiagCursor;
            break;

        default:
            break;
    }

    if (cursor().shape() != shape)
        setCursor(shape);
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        resizeRegion = getResizeRegion(event->pos());
        if (resizeRegion != None) {
            if (window()->windowHandle()) {
                Qt::Edges edges = resizeRegionToEdges(resizeRegion);
                window()->windowHandle()->startSystemResize(edges);
            }

            resizing = true;
            event->accept();
            return;
        }
    }

    QWidget::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        // Не сбрасываем курсор во время системного ресайза
        return QWidget::mouseMoveEvent(event);
    }

    const QRect innerRect = rect().marginsRemoved(QMargins(RESIZE_MARGIN, RESIZE_MARGIN, RESIZE_MARGIN, RESIZE_MARGIN));
    if (!innerRect.contains(event->pos())) {
        updateCursorShape(mapToGlobal(event->pos()));
    } else if (cursor().shape() != Qt::ArrowCursor) {
        setCursor(Qt::ArrowCursor);
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
    updateCursorShape(QCursor::pos());
    QWidget::resizeEvent(event);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    if (getResizeRegion(event->position().toPoint()) == None) {
        isMaximized() ? showNormal() : showMaximized();
    }

    event->accept();
}

Qt::Edges MainWindow::resizeRegionToEdges(ResizeRegion region)
{
    switch(region) {
        case TopLeft: return Qt::TopEdge | Qt::LeftEdge;
        case TopRight: return Qt::TopEdge | Qt::RightEdge;
        case BottomLeft: return Qt::BottomEdge | Qt::LeftEdge;
        case BottomRight: return Qt::BottomEdge | Qt::RightEdge;
        case Top: return Qt::TopEdge;
        case Bottom: return Qt::BottomEdge;
        case Left: return Qt::LeftEdge;
        case Right: return Qt::RightEdge;
        default: return Qt::Edges();
    }
}
