#pragma once
#include "ITokenStorage.h"

class InMemoryTokenStorage : public ITokenStorage
{
public:
    void setAccessToken(QString accessToken) override { m_access = std::move(accessToken); }
    void setRefreshToken(QString refreshToken) override { m_refresh = std::move(refreshToken); }
    void setExpiredAt(QDateTime expiredAt) override { m_expiredAt = std::move(expiredAt); }

    QString   getAccessToken() const override { return m_access; }
    QString   getRefreshToken() const override { return m_refresh; }
    QDateTime getExpiredAt() const override { return m_expiredAt; }

private:
    QString   m_access;
    QString   m_refresh;
    QDateTime m_expiredAt;
};
