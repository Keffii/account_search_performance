#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <sstream>

class BankAccount{
    std::string accountNumber;
    float balance;
public:
    BankAccount(){
    }

    BankAccount(std::string accountNumber, float balance = 0)
    :accountNumber(accountNumber),balance(balance)
    {
        std::ostringstream ss;
        ss << std::setw(10) << std::setfill('0') << accountNumber; // Format: 0000000001. 10 digits long with leading zeros
        this->accountNumber = ss.str();
    }

    std::string getAccountNumber() const{
	    return this->accountNumber;
    }
    
    //Define sorting operator for bankaccount
    bool operator<(const BankAccount& other) const {
        return this->accountNumber < other.accountNumber;
    }
};



//INTERFACE - gränssnitt "standard"
class IAccountStorage {
public:
    virtual ~IAccountStorage() = default;
    virtual void addAccount(BankAccount account) = 0;
	virtual BankAccount *findAccount(std::string accountNumber) = 0;        
};

class MapStorage : public IAccountStorage{
    std::map<std::string,BankAccount> accounts;
public:
    void addAccount(BankAccount account) override{
        accounts[account.getAccountNumber()] = account;
    }
    BankAccount *findAccount(std::string accountNumber){
        return &accounts[accountNumber];
    } 
    
};

//Class binarysearchstorage that implements IAccountStorage interface
class BinarySearchStorage : public IAccountStorage {

private:
    std::vector<BankAccount> accounts;

public:
    void addAccount(BankAccount account) override {
        accounts.push_back(account);
    }

    void sortAccounts(){
        std::sort(accounts.begin(), accounts.end());
    }

    BankAccount *findAccount(std::string accountNumber) override {
        return binarySearch(accountNumber);
    }

    //Iterative binary search
    BankAccount* binarySearch(const std::string& accountNumber){
    int low = 0;
    int high = accounts.size() - 1;
    int step = 1;
    
    while (low <= high){
        auto startTime = std::chrono::high_resolution_clock::now();
        
        int mid = low + (high - low) / 2;
        if (accounts[mid].getAccountNumber() == accountNumber){
            return &accounts[mid];
        }
        
        if (accounts[mid].getAccountNumber() < accountNumber){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
        
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        std::cout << "Binary search step " << step << ": Took " << duration << " nanoseconds" << std::endl;
        step++;
    }
    return nullptr;
    } 
    const std::vector<BankAccount>& getAccounts() const {
        return accounts;
    }

    void printAllAccounts() const {
        for (const auto& account : accounts) {
            std::cout << account.getAccountNumber() << std::endl;
        }
    }
};


class DistributedVectorAccountStorage : public IAccountStorage{
        std::vector<BankAccount> accounts0;
        std::vector<BankAccount> accounts1;
        std::vector<BankAccount> accounts2;
        std::vector<BankAccount> accounts3;
        std::vector<BankAccount> accounts4;
        std::vector<BankAccount> accounts5;
        std::vector<BankAccount> accounts6;
        std::vector<BankAccount> accounts7;
        std::vector<BankAccount> accounts8;
        std::vector<BankAccount> accounts9;
    
    public:
    void addAccount(BankAccount account) override{
        if(account.getAccountNumber().at(0) == '0'){
            accounts0.push_back(account);
        }       
        else if(account.getAccountNumber().at(0) == '1'){
            accounts1.push_back(account);
        }
        else if(account.getAccountNumber().at(0) == '2'){
            accounts2.push_back(account);
        }
        else if(account.getAccountNumber().at(0) == '3'){
            accounts3.push_back(account);
        }
        else if(account.getAccountNumber().at(0) == '4'){
            accounts4.push_back(account);
        }
        else if(account.getAccountNumber().at(0) == '5'){
            accounts5.push_back(account);
        }
        else if(account.getAccountNumber().at(0) == '6'){
            accounts6.push_back(account);
        }
        else if(account.getAccountNumber().at(0) == '7'){
            accounts7.push_back(account);
        }
        else if(account.getAccountNumber().at(0) == '8'){
            accounts8.push_back(account);
        }
        else if(account.getAccountNumber().at(0) == '9'){
            accounts9.push_back(account);
        }
    }

    BankAccount *findAccount( std::string accountNumber){
        BankAccount *ret = nullptr;
        std::vector<BankAccount> &accounts = accounts0;

        if(accountNumber.at(0) == '1'){
            accounts = accounts1;
        }
        if(accountNumber.at(0) == '2'){
            accounts = accounts2;
        }
        if(accountNumber.at(0) == '3'){
            accounts = accounts3;
        }
        if(accountNumber.at(0) == '4'){
            accounts = accounts4;
        }
        if(accountNumber.at(0) == '5'){
            accounts = accounts5;
        }
        if(accountNumber.at(0) == '6'){
            accounts = accounts7;
        }
        if(accountNumber.at(0) == '7'){
            accounts = accounts7;
        }
       if(accountNumber.at(0) == '8'){
            accounts = accounts8;
        }
          if(accountNumber.at(0) == '9'){
            accounts = accounts9;
        }


        for(BankAccount &account : accounts){
            if(account.getAccountNumber() == accountNumber ){
                //ret = &account;      
                return &account;                                  
            }
        }
        return ret;
  

    }

};

class VectorAccountStorage: public IAccountStorage{
        std::vector<BankAccount> accounts;
public:
    void addAccount(BankAccount account) override{
        accounts.push_back(account);
    }

    BankAccount *findAccount(std::string accountNumber){
        BankAccount *ret = nullptr;
        for(BankAccount &account : accounts){
            if(account.getAccountNumber() == accountNumber ){
                //ret = &account;      
                return &account;                                  
            }
        }
        return ret;
    }
    

};




class Bank
{
private:
	IAccountStorage * accountStorage;
public:
	Bank(IAccountStorage *storage):accountStorage(storage){

    }
    bool addAccount(std::string accountNumber){
        //validate
        //if something (accountNumber) return false
        BankAccount account(accountNumber);
        accountStorage->addAccount(account);
        return true;
    }
	BankAccount *getAccount(std::string accountNumber){
        return accountStorage->findAccount(accountNumber);
    }
};



int main(int, char**){
    const int accountAmount = 10;
    BinarySearchStorage storage;
    Bank bank(&storage);

    // Generate and shuffle account 
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

    // Print first and last account numbers
    std::cout << "First account number: " << sFirst << std::endl;
    std::cout << "Last account number: " << sLast << std::endl;

    // Print all account numbers
    std::cout << "All account numbers:" << std::endl;
    storage.printAllAccounts();

    // Sort accounts
    startTime = std::chrono::high_resolution_clock::now();
    storage.sortAccounts();
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << "Sort took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    BankAccount* p = bank.getAccount(sFirst);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sLast);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sNotFound);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << "NOT FOUND" << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds" << std::endl;

    return 0;
}