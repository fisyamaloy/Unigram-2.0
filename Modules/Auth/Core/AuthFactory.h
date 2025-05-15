#ifndef AUTHFACTORY_H
#define AUTHFACTORY_H

#include <memory>
#include <stdexcept>

#include "AuthStrategy.h"
#include "LoginPasswordAuth.h"
#include "PhoneNumberAuth.h"
#include "QRCodeAuth.h"

enum class AuthType { 
    LOGIN_PASSWORD, 
    PHONE, 
    QR 
};

class AuthFactory {
public:
    static std::unique_ptr<AuthStrategy> create(AuthType type) {
        switch (type) {
            case AuthType::LOGIN_PASSWORD:
                return std::make_unique<LoginPasswordAuth>();
            case AuthType::PHONE:
                return std::make_unique<PhoneNumberAuth>();
            case AuthType::QR:
                return std::make_unique<QRCodeAuth>();
            default:
                throw std::invalid_argument("Unknown auth type");
        }
    }
};

#endif // AUTHFACTORY_H
