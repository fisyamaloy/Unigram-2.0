#ifndef QRCODEUI_H
#define QRCODEUI_H

#include <QWidget>

#include "IAuthUI.h"

class QRCodeUI : public QObject, public IAuthUI
{
public:
    QRCodeUI();
    QWidget* widget() override
    {
        // Returns Phone - QR code form
        return nullptr;
    }

    QObject* asQObject() override { return this; }
};

#endif  // QRCODEUI_H
