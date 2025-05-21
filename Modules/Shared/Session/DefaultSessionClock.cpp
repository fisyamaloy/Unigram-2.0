#pragma once
#include "ISessionClock.h"

class DefaultSessionClock : public ISessionClock
{
public:
    QDateTime now() const override { return QDateTime::currentDateTimeUtc(); }
};
