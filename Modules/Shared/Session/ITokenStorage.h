#pragma once

#include <QDateTime>
#include <QString>

class ITokenStorage
{
public:
    virtual ~ITokenStorage() = default;

    virtual void setAccessToken(QString accessToken)   = 0;
    virtual void setRefreshToken(QString refreshToken) = 0;
    virtual void setExpiredAt(QDateTime expiredAt)     = 0;

    virtual QString   getAccessToken() const  = 0;
    virtual QString   getRefreshToken() const = 0;
    virtual QDateTime getExpiredAt() const    = 0;
};
