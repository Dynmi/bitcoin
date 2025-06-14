#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <string>
#include <map>
#include "Block.h"
#include "Transaction.h"
#include "UTXO.h"
#include "Wallet.h"

class Blockchain {
private:
    std::vector<Block> chain;
    std::vector<Transaction> pendingTransactions;
    int difficulty;
    double miningReward;
    
    // UTXO池
    std::map<std::string, UTXO> utxoPool;

public:
    Blockchain();
    
    void addTransaction(const Transaction& transaction);
    void minePendingTransactions(const std::string& minerAddress);
    double getBalanceOfAddress(const std::string& address);
    bool isChainValid() const;
    
    // UTXO相关方法
    void addUTXO(const UTXO& utxo);
    void spendUTXO(const std::string& txId, int outputIndex);
    std::vector<UTXO> getUTXOsForAddress(const std::string& address);
    bool validateTransaction(const Transaction& transaction);
    
    // Getters
    std::vector<Block> getChain() const { return chain; }
    std::vector<Transaction> getPendingTransactions() const { return pendingTransactions; }
    const std::map<std::string, UTXO>& getUTXOPool() const { return utxoPool; }
};

#endif 