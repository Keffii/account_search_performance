#include "BankAccount.h"

BankAccount::BankAccount() {}

BankAccount::BankAccount(std::string accountNumber, float balance)
    : accountNumber(accountNumber), balance(balance) {
    std::ostringstream ss;
    ss << std::setw(10) << std::setfill('0') << accountNumber; // Format: 0000000001. 10 digits long with leading zeros
    this->accountNumber = ss.str();
}

std::string BankAccount::getAccountNumber() const {
    return this->accountNumber;
}

bool BankAccount::operator<(const BankAccount& other) const {
    return this->accountNumber < other.accountNumber;
}