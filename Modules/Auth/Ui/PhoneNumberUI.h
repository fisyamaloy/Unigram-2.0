#ifndef PHONENUMBERUI_H
#define PHONENUMBERUI_H

#include "IAuthUI.h"
#include <QWidget>

class PhoneNumberUI : public IAuthUI {
public:
    PhoneNumberUI();
    QWidget* widget() override {
        // Returns Phone number form
        return nullptr;
    }
};

#endif // PHONENUMBERUI_H
