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

    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    AuthModule authModule; 
    TitleBarWidget* pTitleBar;

    bool resizing = false;
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
};
#endif // MAINWINDOW_H
