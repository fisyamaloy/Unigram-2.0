#ifndef TITLE_BAR_H
#include <QWidget>

class QPushButton;
class QLabel;

#include <QFrame>

class QPushButton;
class QLabel;

class TitleBarWidget : public QFrame {
    Q_OBJECT

public:
    explicit TitleBarWidget(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPoint m_dragPosition;
};

#endif // !TITLE_BAR_H
