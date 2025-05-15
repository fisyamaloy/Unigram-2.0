#ifndef AUTHMODULE_H
#define AUTHMODULE_H

#include <memory>
#include "Core/AuthStrategy.h"
#include "Ui/IAuthUI.h"

struct AuthModule {
    std::unique_ptr<AuthStrategy> strategy;
    std::unique_ptr<IAuthUI> ui;
};

#endif // AUTHMODULE_H
