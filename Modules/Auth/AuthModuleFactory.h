#ifndef AUTH_MODULE_FACTORY

#include <memory>

#include "AuthModule.h"
#include "Core/AuthFactory.h"
#include "Ui/LoginPasswordPage.h"
#include "Ui/PhoneNumberPage.h"
#include "Ui/QRCodePage.h"

class AuthModuleFactory
{
public:
    static AuthModule create(AuthType type)
    {
        switch (type)
        {
            case AuthType::LOGIN_PASSWORD:
                return {std::make_unique<LoginPasswordAuth>(), std::make_unique<LoginPasswordPage>()};
            case AuthType::PHONE:
                return {std::make_unique<PhoneNumberAuth>(), std::make_unique<PhoneNumberPage>()};
            case AuthType::QR:
                return {std::make_unique<QRCodeAuth>(), std::make_unique<QRCodePage>()};
        }
        throw std::invalid_argument("Unknown type");
    }
};

#endif  // !AUTH_MODULE_FACTORY