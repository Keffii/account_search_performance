#include "BinarySearchStorage.h"
#include <algorithm>
#include <chrono>
#include <iostream>

void BinarySearchStorage::addAccount(BankAccount account) {
    accounts.push_back(account);
}

void BinarySearchStorage::sortAccounts() {
    std::sort(accounts.begin(), accounts.end());
}

BankAccount* BinarySearchStorage::findAccount(std::string accountNumber) {
    std::ofstream outFile("bank.txt", std::ios::app);
    return binarySearch(accountNumber, outFile);
}

BankAccount* BinarySearchStorage::binarySearch(const std::string& accountNumber, std::ofstream& outFile) {
    int low = 0;
    int high = accounts.size() - 1;
    int step = 1;

    while (low <= high) {
        auto startTime = std::chrono::high_resolution_clock::now();

        int mid = low + (high - low) / 2;
        if (accounts[mid].getAccountNumber() == accountNumber) {
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
            std::cout << "Binary search step " << step << ": Took " << duration << " nanoseconds" << std::endl;
            outFile << "Binary search step " << step << ": Took " << duration << " nanoseconds" << std::endl;
            return &accounts[mid];
        }

        if (accounts[mid].getAccountNumber() < accountNumber) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        std::cout << "Binary search step " << step << ": Took " << duration << " nanoseconds" << std::endl;
        outFile << "Binary search step " << step << ": Took " << duration << " nanoseconds" << std::endl;
        step++;
    }
    return nullptr;
}

void BinarySearchStorage::printAllAccounts(std::ofstream& outFile) const {
    for (const auto& account : accounts) {
        std::cout << account.getAccountNumber() << std::endl;
        outFile << account.getAccountNumber() << std::endl;
    }
}

const std::vector<BankAccount>& BinarySearchStorage::getAccounts() const {
    return accounts;
}