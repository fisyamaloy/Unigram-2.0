#ifndef IAUTHPAGE_H
#define IAUTHPAGE_H

#include <QObject>

class IAuthPage {
public:
    virtual ~IAuthPage() = default;
    virtual QWidget* widget() = 0;

    // Need to pass signal through QObject
    virtual QObject* asQObject() = 0;
};

#endif // !IAUTHPAGE_H
