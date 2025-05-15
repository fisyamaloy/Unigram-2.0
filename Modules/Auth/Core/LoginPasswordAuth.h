#ifndef LOGINPASSWORDAUTH_H
#define LOGINPASSWORDAUTH_H

#include "AuthStrategy.h"

class LoginPasswordAuth : public AuthStrategy {
public:
    LoginPasswordAuth();
    bool authenticate() override;
};

#endif // LOGINPASSWORDAUTH_H
