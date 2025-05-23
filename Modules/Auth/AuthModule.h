#ifndef AUTHMODULE_H
#define AUTHMODULE_H

#include <memory>
#include "Core/AuthStrategy.h"
#include "Ui/IAuthPage.h"

struct AuthModule {
    std::unique_ptr<AuthStrategy> strategy;
    std::unique_ptr<IAuthPage> ui;
};

#endif // AUTHMODULE_H
