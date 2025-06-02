#ifndef AUTO_GROWING_TEXT_EDIT_H
#define AUTO_GROWING_TEXT_EDIT_H

#include <QTextEdit>

class AutoGrowingTextEdit : public QTextEdit {
    Q_OBJECT

public:
    explicit AutoGrowingTextEdit(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;
    //QSize sizeHint() const override;

private slots:
    void updateHeight();

private:
    static constexpr int MINIMUN_HEIGHT = 30;
    static constexpr int MAXIMUM_HEIGHT = 200;
};

#endif // !AUTO_GROWING_TEXT_EDIT_H
