#ifndef BINARYSEARCHSTORAGE_H
#define BINARYSEARCHSTORAGE_H

#include "IAccountStorage.h"
#include <vector>
#include <fstream>

class BinarySearchStorage : public IAccountStorage {
private:
    std::vector<BankAccount> accounts;

public:
    void addAccount(BankAccount account) override;
    void sortAccounts();
    BankAccount* findAccount(std::string accountNumber) override;
    BankAccount* binarySearch(const std::string& accountNumber, std::ofstream& outFile);
    void printAllAccounts(std::ofstream& outFile) const;
    const std::vector<BankAccount>& getAccounts() const;
};

#endif