#include "RegistrationPage.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

RegistrationPage::RegistrationPage(QWidget* parent) : QWidget(parent) 
{
    auto* pLayout = new QVBoxLayout(this);
    setMinimumSize(860, 650);

    auto* pPhoneLineEdit = new QLineEdit;
    auto* pUsernameLineEdit = new QLineEdit;
    auto* pPasswordLineEdit = new QLineEdit;
    auto* pRepeatPasswordLineEdit = new QLineEdit;
    pPhoneLineEdit->setPlaceholderText("Phone");
    pUsernameLineEdit->setPlaceholderText("Username");
    pPasswordLineEdit->setPlaceholderText("Password");
    pRepeatPasswordLineEdit->setPlaceholderText("Repeat password");

    pPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
    pRepeatPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

    auto* pRegisterButton = new QPushButton("Register");

    pPhoneLineEdit->setMinimumSize(500, 50);
    pUsernameLineEdit->setMinimumSize(500, 50);
    pPasswordLineEdit->setMinimumSize(500, 50);
    pRepeatPasswordLineEdit->setMinimumSize(500, 50);
    pRegisterButton->setMinimumSize(500, 50);

    pPhoneLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pUsernameLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pPasswordLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pRepeatPasswordLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pRegisterButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    pRegisterButton->setFocusPolicy(Qt::NoFocus);

    pLayout->setSpacing(15);

    pLayout->addStretch();
    pLayout->addWidget(pPhoneLineEdit);
    pLayout->addWidget(pUsernameLineEdit);
    pLayout->addWidget(pPasswordLineEdit);
    pLayout->addWidget(pRepeatPasswordLineEdit);
    pLayout->addSpacing(20);
    pLayout->addWidget(pRegisterButton);
    pLayout->addStretch();

    pLayout->setContentsMargins(30, 30, 30, 30);
    pLayout->setAlignment(Qt::AlignHCenter);
}
