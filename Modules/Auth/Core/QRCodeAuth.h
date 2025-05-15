#ifndef QRCODEAUTH_H
#define QRCODEAUTH_H

#include "AuthStrategy.h"

class QRCodeAuth : public AuthStrategy
{
public:
    QRCodeAuth();

    bool authenticate() override;
};

#endif // QRCODEAUTH_H
