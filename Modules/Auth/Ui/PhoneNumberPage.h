#ifndef PHONENUMBERPAGE_H
#define PHONENUMBERPAGE_H

#include <QWidget>

#include "IAuthPage.h"

class PhoneNumberPage : public QObject, public IAuthPage
{
public:
    PhoneNumberPage();
    QWidget* widget() override
    {
        // Returns Phone number form
        return nullptr;
    }

    QObject* asQObject() override { return this; }
};

#endif  // !PHONENUMBERPAGE_H
