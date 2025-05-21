#ifndef IAUTHUI_H
#define IAUTHUI_H

#include <QObject>

class IAuthUI {
public:
    virtual ~IAuthUI() = default;
    virtual QWidget* widget() = 0;

    // Need to pass signal through QObject
    virtual QObject* asQObject() = 0;
};

#endif // IAUTHUI_H
