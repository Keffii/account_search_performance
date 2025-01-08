#ifndef BINARYSEARCHSTORAGE_H
#define BINARYSEARCHSTORAGE_H
#include "IAccountStorage.h"
#include <vector>

class BinarySearchStorage : public IAccountStorage {
private:
    std::vector<BankAccount> accounts;
public:
    void addAccount(BankAccount account) override;
    void sortAccounts();
    BankAccount* findAccount(std::string accountNumber, int& foundAtStep) override;
    BankAccount* binarySearch(const std::string& accountNumber, int& foundAtStep);
    void printAllAccounts() const;
};
#endif