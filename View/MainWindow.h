#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <Modules/Auth/AuthModule.h>

class TitleBarWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    AuthModule authModule; 
    TitleBarWidget* pTitleBar;

    bool m_moving = false;
    bool resizing = false;
    QPoint m_dragOffset;
    QPoint dragStartPos;
    QRect originalGeometry;

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
    ResizeRegion resizeRegion = None;

    ResizeRegion getResizeRegion(const QPoint &pos);
    void updateCursorShape(const QPoint &pos);
    Qt::Edges MainWindow::resizeRegionToEdges(ResizeRegion region);
};
#endif // MAINWINDOW_H
