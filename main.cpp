#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <chrono>

class BankAccount {
    std::string accountNumber;
    float balance;
public:
    BankAccount() {}

    BankAccount(std::string accountNumber, float balance = 0)
        : accountNumber(accountNumber), balance(balance) {}

    std::string getAccountNumber() {
        return this->accountNumber;
    }
};

// INTERFACE - gränssnitt "standard"
class IAccountStorage {
public:
    virtual void addAccount(BankAccount account) = 0;
    virtual BankAccount* findAccount(std::string accountNumber) = 0;
};

class MapStorage : public IAccountStorage {
    std::map<std::string, BankAccount> accounts;
public:
    void addAccount(BankAccount account) override {
        accounts[account.getAccountNumber()] = account;
    }
    BankAccount* findAccount(std::string accountNumber) override {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            return &it->second;
        }
        return nullptr;
    }
};

class DistributedVectorAccountStorage : public IAccountStorage {
    std::vector<BankAccount> accounts0, accounts1, accounts2, accounts3, accounts4;
    std::vector<BankAccount> accounts5, accounts6, accounts7, accounts8, accounts9;

public:
    void addAccount(BankAccount account) override {
        char firstDigit = account.getAccountNumber().at(0);
        switch (firstDigit) {
            case '0': accounts0.push_back(account); break;
            case '1': accounts1.push_back(account); break;
            case '2': accounts2.push_back(account); break;
            case '3': accounts3.push_back(account); break;
            case '4': accounts4.push_back(account); break;
            case '5': accounts5.push_back(account); break;
            case '6': accounts6.push_back(account); break;
            case '7': accounts7.push_back(account); break;
            case '8': accounts8.push_back(account); break;
            case '9': accounts9.push_back(account); break;
        }
    }

    BankAccount* findAccount(std::string accountNumber) override {
        char firstDigit = accountNumber.at(0);
        if (firstDigit < '0' || firstDigit > '9') {
            return nullptr; // Ogiltigt första tecken
        }

        std::vector<BankAccount>* accounts = nullptr;

        switch (firstDigit) {
            case '0': accounts = &accounts0; break;
            case '1': accounts = &accounts1; break;
            case '2': accounts = &accounts2; break;
            case '3': accounts = &accounts3; break;
            case '4': accounts = &accounts4; break;
            case '5': accounts = &accounts5; break;
            case '6': accounts = &accounts6; break;
            case '7': accounts = &accounts7; break;
            case '8': accounts = &accounts8; break;
            case '9': accounts = &accounts9; break;
        }

        for (auto& account : *accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }
};

class VectorAccountStorage : public IAccountStorage {
    std::vector<BankAccount> accounts;
public:
    void addAccount(BankAccount account) override {
        accounts.push_back(account);
    }

    BankAccount* findAccount(std::string accountNumber) override {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }
};

class Bank {
private:
    IAccountStorage* accountStorage;
public:
    Bank(IAccountStorage* storage) : accountStorage(storage) {}

    bool addAccount(std::string accountNumber) {
        accountStorage->addAccount(BankAccount(accountNumber));
        return true;
    }

    BankAccount* getAccount(std::string accountNumber) {
        return accountStorage->findAccount(accountNumber);
    }
};

template <typename T, std::size_t Size>
class Queue {
private:
    T data[Size];
    std::size_t front = 0;
    std::size_t rear = 0;
    std::size_t count = 0;

public:
    bool enqueue(const T& item) {
        if (isFull()) {
            return false;
        }
        data[rear] = item;
        rear = (rear + 1) % Size;
        ++count;
        return true;
    }

    std::optional<T> dequeue() {
        if (isEmpty()) {
            return std::nullopt;
        }
        T item = data[front];
        front = (front + 1) % Size;
        --count;
        return item;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == Size;
    }

    std::size_t size() const {
        return count;
    }
};

int main() {
    DistributedVectorAccountStorage storage;
    Bank bank(&storage);

    const int AntalAccounts = 10000000;

    std::string sFirst = "";
    std::string sLast = "";
    std::string sNotFound = "notfound";

    std::cout << "INITIALIZE: " << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < AntalAccounts; i++) {
        std::string accountNumber = std::to_string(i);
        if (i == 0) {
            sFirst = accountNumber;
        }
        if (i == AntalAccounts - 1) {
            sLast = accountNumber;
        }
        bank.addAccount(accountNumber);
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << "INIT Took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
              << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    BankAccount* p = bank.getAccount(sFirst);
    endTime = std::chrono::high_resolution_clock::now();

    if (p) {
        std::cout << p->getAccountNumber() << " took: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
                  << " milliseconds" << std::endl;
    }

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sLast);
    endTime = std::chrono::high_resolution_clock::now();

    if (p) {
        std::cout << p->getAccountNumber() << " took: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
                  << " milliseconds" << std::endl;
    }

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sNotFound);
    endTime = std::chrono::high_resolution_clock::now();

    if (p) {
        std::cout << p->getAccountNumber() << " took: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
                  << " milliseconds" << std::endl;
    } else {
        std::cout << "NOT FOUND took: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
                  << " milliseconds" << std::endl;
    }

    constexpr std::size_t queueStorlek = 5;
    Queue<int, queueStorlek> q;

    for (int i = 0; i < 6; ++i) {
        if (q.enqueue(i)) {
            std::cout << "enqueued: " << i << "\n";
        } else {
            std::cout << "queue is full. Failed to enqueue: " << i << "\n";
        }
    }

    while (!q.isEmpty()) {
        auto item = q.dequeue();
        if (item) {
            std::cout << "dequeued: " << *item << "\n";
        }
    }

    auto item = q.dequeue();
    if (!item) {
        std::cout << "queue is empty. Nothing to dequeue.\n";
    }

    return 0;
}
