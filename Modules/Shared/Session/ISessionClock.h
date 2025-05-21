#pragma once
#include <QDateTime>

class ISessionClock
{
public:
    virtual ~ISessionClock()      = default;
    virtual QDateTime now() const = 0;
};
