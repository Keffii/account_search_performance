#ifndef IACCOUNTSTORAGE_H
#define IACCOUNTSTORAGE_H
#include "BankAccount.h"

class IAccountStorage {
public:
    virtual ~IAccountStorage() = default;
    virtual void addAccount(BankAccount account) = 0;
    virtual BankAccount* findAccount(std::string accountNumber, int& foundAtStep) = 0;
};
#endif