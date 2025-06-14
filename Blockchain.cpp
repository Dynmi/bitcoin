#include "Blockchain.h"
#include <iostream>

Blockchain::Blockchain() : difficulty(4), miningReward(100.0) {
    // Create genesis block
    std::vector<Transaction> genesisTransactions;
    chain.push_back(Block(0, "0", genesisTransactions));
}

void Blockchain::addTransaction(const Transaction& transaction) {
    pendingTransactions.push_back(transaction);
}

void Blockchain::minePendingTransactions(const std::string& minerAddress) {
    // Create mining reward transaction
    Transaction rewardTx("system", minerAddress, miningReward);
    pendingTransactions.push_back(rewardTx);
    
    // Create new block with pending transactions
    Block newBlock(chain.size(), chain.back().getHash(), pendingTransactions);
    newBlock.mineBlock(difficulty);
    
    // Add block to chain
    chain.push_back(newBlock);
    
    // Clear pending transactions
    pendingTransactions.clear();
}

double Blockchain::getBalanceOfAddress(const std::string& address) {
    double balance = 0.0;
    
    for(const auto& block : chain) {
        for(const auto& tx : block.getTransactions()) {
            if(tx.getSender() == address) {
                balance -= tx.getAmount();
            }
            if(tx.getRecipient() == address) {
                balance += tx.getAmount();
            }
        }
    }
    
    return balance;
}

bool Blockchain::isChainValid() const {
    for(size_t i = 1; i < chain.size(); i++) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i-1];
        
        // Check if current block's hash is valid
        if(currentBlock.getHash() != currentBlock.calculateHash()) {
            return false;
        }
        
        // Check if current block points to previous block
        if(currentBlock.getPreviousHash() != previousBlock.getHash()) {
            return false;
        }
    }
    return true;
} 