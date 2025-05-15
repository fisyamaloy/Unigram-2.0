#ifndef QRCODEUI_H
#define QRCODEUI_H

#include "IAuthUI.h"
#include <QWidget>

class QRCodeUI : public IAuthUI {
public:
    QRCodeUI();
    QWidget* widget() override {
        // Returns Phone - QR code form
        return nullptr;
    }
};

#endif // QRCODEUI_H
