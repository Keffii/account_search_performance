#ifndef BANK_H
#define BANK_H

#include "IAccountStorage.h"

class Bank {
private:
    IAccountStorage* accountStorage;
public:
    Bank(IAccountStorage* storage);
    bool addAccount(std::string accountNumber);
    BankAccount* getAccount(std::string accountNumber);
};

#endif