#include "../Header/Bank.h"
#include <fstream>

Bank::Bank(IAccountStorage* storage) : accountStorage(storage) {}

bool Bank::addAccount(std::string accountNumber) {
    BankAccount account(accountNumber);
    accountStorage->addAccount(account);
    return true;
}

BankAccount* Bank::getAccount(std::string accountNumber, int& foundAtStep) {
    return accountStorage->findAccount(accountNumber, foundAtStep);
}