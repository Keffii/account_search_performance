#include "../Header/Bank.h"
#include <fstream>

Bank::Bank(IAccountStorage* storage) : accountStorage(storage) {}

bool Bank::addAccount(std::string accountNumber) {
    BankAccount account(accountNumber);
    accountStorage->addAccount(account);
    return true;
}

BankAccount* Bank::getAccount(std::string accountNumber) {
    std::ofstream outFile("bank.txt", std::ios::app);
    return accountStorage->findAccount(accountNumber);
}