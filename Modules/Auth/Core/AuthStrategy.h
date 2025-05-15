#ifndef AUTHSTRATEGY_H
#define AUTHSTRATEGY_H

class AuthStrategy {
public:
    virtual ~AuthStrategy() = default;
    virtual bool authenticate() = 0;
};

#endif // AUTHSTRATEGY_H
