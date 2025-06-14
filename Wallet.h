#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>
#include "Transaction.h"

class Wallet {
private:
    std::string publicKey;
    double balance;
    std::vector<Transaction> transactionHistory;

public:
    Wallet();
    std::string getPublicKey() const { return publicKey; }
    double getBalance() const { return balance; }
    
    void addTransaction(const Transaction& transaction);
    void updateBalance(double amount);
    std::vector<Transaction> getTransactionHistory() const { return transactionHistory; }
};

#endif 