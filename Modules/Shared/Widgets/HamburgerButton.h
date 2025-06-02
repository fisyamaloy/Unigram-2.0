#ifndef HAMBURGER_BUTTON_H

#include <QPushButton>

class HamburgerButton : public QPushButton
{
    Q_OBJECT
public:
    explicit HamburgerButton(QWidget* parent = nullptr);
};

#endif  // !HAMBURGER_BUTTON_H
