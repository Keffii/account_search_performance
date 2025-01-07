#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <sstream>
#include <iomanip>

class BankAccount {
    std::string accountNumber;
    float balance;
public:
    BankAccount();
    BankAccount(std::string accountNumber, float balance = 0);
    std::string getAccountNumber() const;
    bool operator<(const BankAccount& other) const;
};

#endif