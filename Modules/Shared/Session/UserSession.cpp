#include "UserSession.h"

UserSession::UserSession(std::shared_ptr<ITokenStorage> tokenStorage, std::shared_ptr<ISessionClock> clock)
    : m_tokenStorage(std::move(tokenStorage)), m_clock(std::move(clock))
{
}

void UserSession::login(QString username, const int userId, QString accessToken, QString refreshToken, QDateTime expiredAt)
{
    m_data.username = std::move(username);
    m_data.userId   = userId;

    m_tokenStorage->setAccessToken(std::move(accessToken));
    m_tokenStorage->setRefreshToken(std::move(refreshToken));
    m_tokenStorage->setExpiredAt(std::move(expiredAt));
}

void UserSession::logout()
{
    m_data.clear();
    m_tokenStorage->setAccessToken({});
    m_tokenStorage->setRefreshToken({});
    m_tokenStorage->setExpiredAt({});
}
