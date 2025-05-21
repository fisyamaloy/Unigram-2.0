#ifndef LOGINPASSWORDUI_H
#define LOGINPASSWORDUI_H

#include "IAuthUI.h"
#include <QObject>

class LoginPasswordUI : public QObject, public IAuthUI {
    Q_OBJECT
public:
    LoginPasswordUI();
    QWidget* widget() override;
    QObject* asQObject() override;

signals:
    void goToChatPage();
    void goToRegistrationPage();
};

#endif // LOGINPASSWORDUI_H
