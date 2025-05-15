#ifndef IAUTHUI_H
#define IAUTHUI_H

#include <QWidget>

class IAuthUI {
public:
    virtual ~IAuthUI() = default;
    virtual QWidget* widget() = 0;
};

#endif // IAUTHUI_H
