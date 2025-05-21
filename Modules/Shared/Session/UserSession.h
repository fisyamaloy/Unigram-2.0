#pragma once

#include <memory>

#include "ISessionClock.h"
#include "ITokenStorage.h"
#include "SessionData.h"

class UserSession
{
public:
    UserSession(std::shared_ptr<ITokenStorage> tokenStorage, std::shared_ptr<ISessionClock> clock);

    void login(QString username, const int userId, QString accessToken, QString refreshToken, QDateTime expiredAt);
    void logout();

    inline bool    isLoggedIn() const { return m_data.isValid(); }
    inline int     getUserId() const { return m_data.userId; }
    inline QString getUsername() const { return m_data.username; }
    inline bool    isExpired() const { return m_clock->now() > m_tokenStorage->getExpiredAt(); }

private:
    SessionData m_data;

    std::shared_ptr<ITokenStorage> m_tokenStorage;
    std::shared_ptr<ISessionClock> m_clock;
};
