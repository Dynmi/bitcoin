#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <string>
#include "Block.h"
#include "Transaction.h"
#include "Wallet.h"

class Blockchain {
private:
    std::vector<Block> chain;
    std::vector<Transaction> pendingTransactions;
    int difficulty;
    double miningReward;

public:
    Blockchain();
    
    void addTransaction(const Transaction& transaction);
    void minePendingTransactions(const std::string& minerAddress);
    double getBalanceOfAddress(const std::string& address);
    bool isChainValid() const;
    
    // Getters
    std::vector<Block> getChain() const { return chain; }
    std::vector<Transaction> getPendingTransactions() const { return pendingTransactions; }
};

#endif 