#ifndef AUTH_MODULE_FACTORY

#include <memory>

#include "AuthModule.h"
#include "Core/AuthFactory.h"
#include "Ui/LoginPasswordUI.h"
#include "Ui/PhoneNumberUI.h"
#include "Ui/QRCodeUI.h"

class AuthModuleFactory
{
public:
    static AuthModule create(AuthType type)
    {
        switch (type)
        {
            case AuthType::LOGIN_PASSWORD:
                return {std::make_unique<LoginPasswordAuth>(), std::make_unique<LoginPasswordUI>()};
            case AuthType::PHONE:
                return {std::make_unique<PhoneNumberAuth>(), std::make_unique<PhoneNumberUI>()};
            case AuthType::QR:
                return {std::make_unique<QRCodeAuth>(), std::make_unique<QRCodeUI>()};
        }
        throw std::invalid_argument("Unknown type");
    }
};

#endif  // !AUTH_MODULE_FACTORY