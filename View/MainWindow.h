#ifndef MAINWINDOW_H

#include <Modules/Auth/AuthModule.h>
#include <Ui/RegistrationPage.h>

#include <QMargins>
#include <QMouseEvent>
#include <QPoint>
#include <QResizeEvent>
#include <QWidget>

class TitleBarWidget;
class QStackedWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void onGoToRegistration();
    void onGoToChat();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    constexpr static int RESIZE_MARGIN = 5;

    enum ResizeRegion
    {
        None,
        Left,
        Right,
        Top,
        Bottom,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    AuthModule        m_authModule;
    QStackedWidget*   m_pagesStack       = nullptr;
    TitleBarWidget*   m_titleBar         = nullptr;
    RegistrationPage* m_registrationPage = nullptr;

    bool         m_moving   = false;
    bool         m_resizing = false;
    QPoint       m_dragOffset;
    ResizeRegion m_resizeRegion = None;

    ResizeRegion getResizeRegion(const QPoint& pos);
    void         updateCursorShape(const QPoint& globalPos);
    Qt::Edges    resizeRegionToEdges(ResizeRegion region);
};

#endif  // MAINWINDOW_H
