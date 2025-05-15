#ifndef PHONENUMBERAUTH_H
#define PHONENUMBERAUTH_H

#include "AuthStrategy.h"

class PhoneNumberAuth : public AuthStrategy
{
public:
    PhoneNumberAuth();
    bool authenticate() override;
};

#endif // PHONENUMBERAUTH_H
