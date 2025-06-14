#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <ctime>
#include "Transaction.h"

class Block {
private:
    int index;
    std::string previousHash;
    std::string hash;
    std::vector<Transaction> transactions;
    time_t timestamp;
    int nonce;

public:
    Block(int idx, const std::string& prevHash, const std::vector<Transaction>& txs);
    
    std::string calculateHash() const;
    void mineBlock(int difficulty);
    
    // Getters
    std::string getHash() const { return hash; }
    std::string getPreviousHash() const { return previousHash; }
    std::vector<Transaction> getTransactions() const { return transactions; }
    int getIndex() const { return index; }
};

#endif 