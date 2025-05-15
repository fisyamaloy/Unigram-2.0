#ifndef LOGINPASSWORDUI_H
#define LOGINPASSWORDUI_H

#include "IAuthUI.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

class LoginPasswordUI : public IAuthUI {
public:
    LoginPasswordUI();
    QWidget* widget() override {
        auto pWidget = new QWidget;
        auto pLayout = new QVBoxLayout;
        pWidget->setMinimumSize(860, 650);
        
        auto pUsernameLineEdit = new QLineEdit;
        auto pPasswordLineEdit = new QLineEdit;
        pUsernameLineEdit->setPlaceholderText("Username");
        pPasswordLineEdit->setPlaceholderText("Password");
        pPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        auto pLoginButton = new QPushButton("Login");
        auto pRegistrationButton = new QPushButton("Registration");

        pUsernameLineEdit->setMinimumSize(500, 50);
        pPasswordLineEdit->setMinimumSize(500, 50);
        pLoginButton->setMinimumSize(500, 50);
        pRegistrationButton->setMinimumSize(500, 50);

        pUsernameLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        pPasswordLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        pLoginButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        pRegistrationButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        // QFont font;
        // font.setPixelSize(18);
        // pUsernameLineEdit->setFont(font);
        // pPasswordLineEdit->setFont(font);
        
        pLayout->setSpacing(15);
        
        pLayout->addStretch();
        pLayout->addWidget(pUsernameLineEdit);
        pLayout->addWidget(pPasswordLineEdit);
        pLayout->addSpacing(20);
        pLayout->addWidget(pLoginButton);
        pLayout->addWidget(pRegistrationButton);
        pLayout->addStretch();
        
        pLayout->setContentsMargins(30, 30, 30, 30); 
        pLayout->setAlignment(Qt::AlignHCenter);

        pWidget->setLayout(pLayout);
        
        return pWidget;
    }
};

#endif // LOGINPASSWORDUI_H
