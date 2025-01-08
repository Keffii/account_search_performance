#include "../Header/Bank.h"
#include "../Header/BinarySearchStorage.h"
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <fstream>

int main() {
    // Initialize storage with 10 accounts
    const int accountAmount = 10;
    BinarySearchStorage storage;
    Bank bank(&storage);

    // Create and shuffle numbers 1-10
    std::vector<int> numbers(accountAmount);
    for(int i = 0; i < accountAmount; i++) {
        numbers[i] = i + 1;
    }

    // Use current time as seed for stronger randomization
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(numbers.begin(), numbers.end(), gen);

    // Sort the numbers for binary search
    std::sort(numbers.begin(), numbers.end());

    // Add formatted accounts to storage
    for (const auto& num : numbers) {
        std::ostringstream ss;
        ss << std::setw(10) << std::setfill('0') << num;
        bank.addAccount(ss.str());
    }

    // Write the sorted array to bank.txt
    std::ofstream outFile("bank.txt", std::ios_base::app); // Open file in append mode
    outFile << "Sorted array: " << std::endl;
    for (const auto& num : numbers) {
        outFile << std::setw(10) << std::setfill('0') << num << " " << std::endl;
    }
    outFile << std::endl;

    // Get user input
    int target;
    std::cout << "Enter a number between 1 and 10: ";
    std::cin >> target;

    // Format the target number
    std::ostringstream ss;
    ss << std::setw(10) << std::setfill('0') << target;
    std::string formattedTarget = ss.str();

    // Perform binary search with a maximum of 4 steps
    int steps = 0;
    int foundAtStep = 0;
    BankAccount* foundAccount = nullptr;

    foundAccount = bank.getAccount(formattedTarget, foundAtStep);

    if (foundAccount != nullptr) {
        outFile << "Number " << formattedTarget << " found in " << foundAtStep << " steps.\n" << std::endl;

        // Create and shuffle numbers 1-10
        std::vector<int> randomOrder(accountAmount);
        for(int i = 0; i < accountAmount; i++) {
            randomOrder[i] = i + 1;
        }
        std::shuffle(randomOrder.begin(), randomOrder.end(), gen);

        // Add the found number to the random order
        randomOrder.push_back(target);

        // Print the new random order
        outFile << "New random order with the found number: ";
        for (const auto& num : randomOrder) {
            outFile << num << " ";
        }
        outFile << std::endl;

        // Measure the time taken to sort the random order
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(randomOrder.begin(), randomOrder.end());
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        // Print the sorted random order
        outFile << "Sorted random order: ";
        for (const auto& num : randomOrder) {
            outFile << num << " ";
        }
        outFile << std::endl;

        // Print the time taken to sort
        outFile << "Time taken to sort: " << duration << " nanoseconds." << std::endl;
    } else {
        outFile << "Number " << formattedTarget << " not found within 4 steps." << std::endl;
    }

    outFile.close(); // Close the file

    return 0;
}