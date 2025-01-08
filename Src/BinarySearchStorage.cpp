#include "../Header/BinarySearchStorage.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>

void BinarySearchStorage::addAccount(BankAccount account) {
    accounts.push_back(account);
}

void BinarySearchStorage::sortAccounts() {
    std::sort(accounts.begin(), accounts.end());
}

void BinarySearchStorage::printAllAccounts() const {
    for (const auto& account : accounts) {
        std::cout << account.getAccountNumber() << std::endl;
    }
}

BankAccount* BinarySearchStorage::findAccount(std::string accountNumber, int& foundAtStep) {
    return binarySearch(accountNumber, foundAtStep);
}

BankAccount* BinarySearchStorage::binarySearch(const std::string& accountNumber, int& foundAtStep) {
    int low = 0;
    int high = accounts.size() - 1;
    foundAtStep = 0;

    std::ofstream outFile("bank.txt", std::ios_base::app); // Open file in append mode

    while (low <= high && foundAtStep < 4) {
        foundAtStep++;
        auto startTime = std::chrono::high_resolution_clock::now();

        int mid = low + (high - low) / 2;
        outFile << "Checking position " << mid << " (value: " << accounts[mid].getAccountNumber() << ")" << std::endl;

        if (accounts[mid].getAccountNumber() == accountNumber) {
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
            outFile << "Binary search step " << foundAtStep << ": Found! Took " << duration << " nanoseconds" << std::endl;
            outFile.close();
            return &accounts[mid];
        }

        if (accounts[mid].getAccountNumber() < accountNumber) {
            outFile << "Target " << accountNumber << " is in right half" << std::endl;
            low = mid + 1;
        } else {
            outFile << "Target " << accountNumber << " is in left half" << std::endl;
            high = mid - 1;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        outFile << "Binary search step " << foundAtStep << ": Took " << duration << " nanoseconds" << std::endl << std::endl;
    }

    outFile.close();
    return nullptr;
}