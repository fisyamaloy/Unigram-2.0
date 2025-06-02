#include "MainWindow.h"

#include <QCursor>
#include <QMouseEvent>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWindow>

#include "Modules/Auth/AuthModule.h"
#include "Modules/Auth/AuthModuleFactory.h"
#include "Modules/Auth/Core/AuthFactory.h"
#include <Modules/Shared/Widgets/TitleBar.h>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    m_pagesStack       = new QStackedWidget(this);
    m_registrationPage = new RegistrationPage;
    m_chatPage         = new ChatPage;

    m_pagesStack->addWidget(m_registrationPage);
    m_pagesStack->addWidget(m_chatPage);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    setMouseTracking(true);

    auto pLayout = new QVBoxLayout(this);
    pLayout->setContentsMargins(0, 0, 0, 0);

    m_titleBar = new TitleBarWidget;
    pLayout->addWidget(m_titleBar);

    AuthType selected = AuthType::LOGIN_PASSWORD;
    m_authModule      = AuthModuleFactory::create(selected);
    auto pAuthForm    = m_authModule.ui->widget();
    m_pagesStack->addWidget(pAuthForm);
    //m_pagesStack->setCurrentWidget(pAuthForm);
    m_pagesStack->setCurrentWidget(m_chatPage);

    pLayout->addWidget(m_pagesStack);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    connect(m_titleBar, &TitleBarWidget::beginWindowMove, this, [this](const QPoint& globalPos) {
        if (!m_resizing)
        {
            m_dragOffset = globalPos - frameGeometry().topLeft();
            m_moving     = true;
        }
    });

    connect(m_titleBar, &TitleBarWidget::windowMove, this, [this](const QPoint& globalPos) {
        if (m_moving && !m_resizing)
        {
            move(globalPos - m_dragOffset);
        }
    });

    connect(m_authModule.ui->asQObject(), SIGNAL(goToChatPage()), this, SLOT(onGoToChat()));
    connect(m_authModule.ui->asQObject(), SIGNAL(goToRegistrationPage()), this, SLOT(onGoToRegistration()));

    pAuthForm->setMouseTracking(true);
    
    for (auto* child : m_chatPage->findChildren<QWidget*>()) {
        child->installEventFilter(this);
        child->setMouseTracking(true);
    }

    m_chatPage->installEventFilter(this);
    m_registrationPage->installEventFilter(this);
    pAuthForm->installEventFilter(this);
    m_titleBar->installEventFilter(this);
}

MainWindow::~MainWindow() {}

void MainWindow::onGoToRegistration() { m_pagesStack->setCurrentWidget(m_registrationPage); }

void MainWindow::onGoToChat() { m_pagesStack->setCurrentWidget(m_chatPage); }

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::MouseMove)
    {
        auto mouseEvent = static_cast<QMouseEvent*>(event);
        this->mouseMoveEvent(mouseEvent);

        return false;
    }

    return QWidget::eventFilter(watched, event);
}

MainWindow::ResizeRegion MainWindow::getResizeRegion(const QPoint& pos)
{
    bool left   = pos.x() <= RESIZE_MARGIN;
    bool right  = pos.x() >= width() - RESIZE_MARGIN;
    bool top    = pos.y() <= RESIZE_MARGIN;
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

void MainWindow::updateCursorShape(const QPoint& globalPos)
{
    const QPoint localPos = mapFromGlobal(globalPos);
    const auto   region   = getResizeRegion(localPos);

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

    if (cursor().shape() != shape) setCursor(shape);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_resizeRegion = getResizeRegion(event->pos());
        if (m_resizeRegion != None)
        {
            if (window()->windowHandle())
            {
                Qt::Edges edges = resizeRegionToEdges(m_resizeRegion);
                window()->windowHandle()->startSystemResize(edges);
            }

            m_resizing = true;
            event->accept();
            return;
        }
    }

    QWidget::mousePressEvent(event);
}

static int i = 0;

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    qDebug("MainWindow::mouseMoveEvent %d", i);
    if (event->buttons() & Qt::LeftButton)
    {
        return QWidget::mouseMoveEvent(event);
    }

    const QRect innerRect = rect().marginsRemoved(QMargins(RESIZE_MARGIN, RESIZE_MARGIN, RESIZE_MARGIN, RESIZE_MARGIN));
    if (!innerRect.contains(event->pos()))
    {
        updateCursorShape(mapToGlobal(event->pos()));
    }
    else if (cursor().shape() != Qt::ArrowCursor)
    {
        setCursor(Qt::ArrowCursor);
    }

    QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_resizing     = false;
        m_moving       = false;
        m_resizeRegion = None;
    }

    QWidget::mouseReleaseEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    updateCursorShape(QCursor::pos());
    QWidget::resizeEvent(event);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) return;

    if (getResizeRegion(event->position().toPoint()) == None)
    {
        isMaximized() ? showNormal() : showMaximized();
    }

    event->accept();
}

Qt::Edges MainWindow::resizeRegionToEdges(ResizeRegion region)
{
    switch (region)
    {
        case TopLeft:
            return Qt::TopEdge | Qt::LeftEdge;
        case TopRight:
            return Qt::TopEdge | Qt::RightEdge;
        case BottomLeft:
            return Qt::BottomEdge | Qt::LeftEdge;
        case BottomRight:
            return Qt::BottomEdge | Qt::RightEdge;
        case Top:
            return Qt::TopEdge;
        case Bottom:
            return Qt::BottomEdge;
        case Left:
            return Qt::LeftEdge;
        case Right:
            return Qt::RightEdge;
        default:
            return Qt::Edges();
    }
}
