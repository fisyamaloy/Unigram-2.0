#ifndef PHONENUMBERUI_H
#define PHONENUMBERUI_H

#include <QWidget>

#include "IAuthUI.h"

class PhoneNumberUI : public QObject, public IAuthUI
{
public:
    PhoneNumberUI();
    QWidget* widget() override
    {
        // Returns Phone number form
        return nullptr;
    }

    QObject* asQObject() override { return this; }
};

#endif  // PHONENUMBERUI_H
