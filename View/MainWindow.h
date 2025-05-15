#ifndef MAINWINDOW_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QMargins>
#include <Modules/Auth/AuthModule.h>

class TitleBarWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    enum ResizeRegion {
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

    AuthModule authModule;
    TitleBarWidget* pTitleBar = nullptr;

    bool m_moving = false;
    bool resizing = false;
    QPoint m_dragOffset;
    ResizeRegion resizeRegion = None;

    ResizeRegion getResizeRegion(const QPoint &pos);
    void updateCursorShape(const QPoint &globalPos);
    void updateCursorShapeByResizeRegion(ResizeRegion region);
    Qt::Edges resizeRegionToEdges(ResizeRegion region);
};

#endif // MAINWINDOW_H
