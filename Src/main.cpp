#include "Bank.h"
#include "BinarySearchStorage.h"
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>

int main() {
    std::ofstream outFile("bank.txt");

    const int accountAmount = 10;
    BinarySearchStorage storage;
    Bank bank(&storage);

    // Generate and shuffle account numbers
    std::vector<std::string> accountNumbers(accountAmount);
    for (int i = 0; i < accountAmount; i++) {
        accountNumbers[i] = std::to_string(i);
    }

    // Shuffle account numbers using mersenne twister
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(accountNumbers.begin(), accountNumbers.end(), gen);

    std::string sFirst = ""; 
    std::string sLast = ""; 
    std::string sNotFound = "notfound"; 

    std::cout << "INITIALIZE: " << std::endl;
    outFile << "INITIALIZE: " << std::endl;

    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < accountAmount; i++) {
        std::string accountNumber = accountNumbers[i];
        if (i == 0) {
            sFirst = accountNumber;
        }
        if (i == accountAmount - 1) {
            sLast = accountNumber;
        }
        bank.addAccount(accountNumber);
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    
    std::cout << "INIT Took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;
    outFile << "INIT Took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;

    std::cout << "First account number: " << sFirst << std::endl;
    outFile << "First account number: " << sFirst << std::endl;
    
    std::cout << "Last account number: " << sLast << std::endl;
    outFile << "Last account number: " << sLast << std::endl;

    std::cout << "All account numbers:" << std::endl;
    outFile << "All account numbers:" << std::endl;
    storage.printAllAccounts(outFile);

    startTime = std::chrono::high_resolution_clock::now();
    storage.sortAccounts();
    endTime = std::chrono::high_resolution_clock::now();
    
    std::cout << "Sort took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;
    outFile << "Sort took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;

    // Test search for first account
    startTime = std::chrono::high_resolution_clock::now();
    BankAccount* p = bank.getAccount(sFirst);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;
    outFile << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;

    // Test search for last account
    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sLast);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;
    outFile << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;

    // Test search for non-existent account
    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sNotFound);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << "NOT FOUND" << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;
    outFile << "NOT FOUND" << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;

    outFile.close();
    return 0;
}