#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <chrono>

class BankAccount{
    std::string accountNumber;
    float balance;
public:
    BankAccount(){
    }

    BankAccount(std::string accountNumber, float balance = 0)
    :accountNumber(accountNumber),balance(balance)
    {
    }

    std::string getAccountNumber()
    {
	    return this->accountNumber;
    }
};

//INTERFACE - gränssnitt "standard"
class IAccountStorage {
public:    
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
        accountStorage->addAccount(accountNumber);
        return true;
    }
	BankAccount *getAccount(std::string accountNumber){
        return accountStorage->findAccount(accountNumber);
    }
};


template<typename T, int N>
class RingQueue {
    private:
    T things[N]; //statisk array för lagring
    int front; // index för första elementet 
    int rear; // index där nästa lediga plats kommer att vara
    int count; // Antal element i kön

    public:
    RingQueue() : front(0), rear(0), count(0) {}

    void enqueue(T value) {
        if(isFull()) {
            std::cout << "queue är full, överskriver första elementet!" << std::endl;
            front = (front +1) % N; // flyttar fram front för att ersätta de äldsta elementet
            count--; // Tillfälligt minskar räknaren
        }
        things[rear] = value; // Lägg till det nya elementet
        rear = (rear + 1) % N; // Flytta rear framåt 
        count++; //öka räknaren
    }
//Tar bort och returnerar det första elementet
    T dequeue() {
        if(isEmpty()) {
            throw std::runtime_error("Queue är tom!");
        }
        T value = things[front]; //Hämta det första elementet
        front = (front + 1) % N; // flyttar front framåt
        count--; // Minskar räknaren
        return value;
    }
// Kontrollera om kön är tom
    bool isEmpty() const {
        return count == 0;
    }
    //kontrollerar om kön är full
    bool isFull() const {
        return count == N;
    }
//Skriver ut innehållet i kön, och om den är tom
    void print() const {
        if(isEmpty()) {
            std::cout << "queue är tom" << std::endl;
            return;
        }
        std::cout << "RingQueue: ";
        for(int i = 0; i < count; i++) {
            std::cout << things[(front + i) % N] << " ";
        }
        std::cout << std::endl;
    }
};



int main(int, char**){
    //VectorAccountStorage storage;
    //VectorAccountStorage storage;
    //MapStorage storage;
    DistributedVectorAccountStorage storage;
    //MapAccountStor age storage;
    Bank bank(&storage);

    const int AntalAccounts =  10000000;


    std::string sFirst = ""; 
    std::string sLast = ""; 
    std::string sNotFound = "notfound"; 

    std::cout << "INITIALIZE: " << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now();
    for(int i = 0;i < AntalAccounts; i++){
        std::string accountNumber =  std::to_string(i);
        if(i == 0){
            sFirst = accountNumber;
        }
        if(i == AntalAccounts-1){
            sLast = accountNumber;
        }
        bank.addAccount(accountNumber);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << "INIT Took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    BankAccount *p = bank.getAccount(sFirst);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sLast);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sNotFound);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << "NOT FOUND" << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    RingQueue<int, 5> queue; //Skapar en RingQueue med storlek 5
//Lägger till några element
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.print();
//Lägger till element när kön är full
    queue.enqueue(6); //denna ersätter det första elementet
    queue.print();
//Tar bort några
    std::cout << "Dequeue: " << queue.dequeue() << std::endl;
    std::cout << "Dequeue: " << queue.dequeue() << std::endl;
    queue.print();
//Lägger till igen
    queue.enqueue(7);
    queue.enqueue(8);
    queue.print();
//Tar bort alla element.
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.print();

    return 0;
}



