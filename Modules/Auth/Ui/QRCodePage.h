#ifndef QRCODEPAGE_H
#define QRCODEPAGE_H

#include <QWidget>

#include "IAuthPage.h"

class QRCodePage : public QObject, public IAuthPage
{
public:
    QRCodePage();
    QWidget* widget() override
    {
        // Returns Phone - QR code form
        return nullptr;
    }

    QObject* asQObject() override { return this; }
};

#endif  // QRCODEPAGE_H
