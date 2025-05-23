#ifndef LOGINPASSWORDPAGE_H
#define LOGINPASSWORDPAGE_H

#include "IAuthPage.h"
#include <QObject>

class LoginPasswordPage : public QObject, public IAuthPage {
    Q_OBJECT
public:
    LoginPasswordPage();
    QWidget* widget() override;
    QObject* asQObject() override;

signals:
    void goToChatPage();
    void goToRegistrationPage();
};

#endif // LOGINPASSWORDPAGE_H
