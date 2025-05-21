#pragma once

#include <QString>

struct SessionData
{
    int     userId = -1;
    QString username;

    inline bool isValid() const { return !username.isEmpty() && userId != -1; }
    void clear() 
    { 
        userId = -1; 
        username.clear(); 
    }
};
