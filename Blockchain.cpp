#include "Blockchain.h"
#include <iostream>

Blockchain::Blockchain() : difficulty(4), miningReward(100.0) {
    // Create genesis block
    std::vector<Transaction> genesisTransactions;
    chain.push_back(Block(0, "0", genesisTransactions));
}

void Blockchain::addTransaction(const Transaction& transaction) {
    if (validateTransaction(transaction)) {
        pendingTransactions.push_back(transaction);
        
        // 处理输入UTXO
        for (const auto& input : transaction.getInputs()) {
            spendUTXO(input.first, input.second);
        }
        
        // 处理输出UTXO
        for (size_t i = 0; i < transaction.getOutputs().size(); i++) {
            const auto& output = transaction.getOutputs()[i];
            UTXO newUTXO(transaction.getTransactionId(), i, output.first, output.second);
            addUTXO(newUTXO);
        }
    }
}

void Blockchain::minePendingTransactions(const std::string& minerAddress) {
    // Create mining reward transaction
    Transaction rewardTx("system", minerAddress, miningReward);
    rewardTx.addOutput(minerAddress, miningReward);
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
    for (const auto& utxo : getUTXOsForAddress(address)) {
        balance += utxo.getAmount();
    }
    return balance;
}

bool Blockchain::isChainValid() const {
    for(size_t i = 1; i < chain.size(); i++) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i-1];
        
        if(currentBlock.getHash() != currentBlock.calculateHash()) {
            return false;
        }
        
        if(currentBlock.getPreviousHash() != previousBlock.getHash()) {
            return false;
        }
    }
    return true;
}

void Blockchain::addUTXO(const UTXO& utxo) {
    utxoPool[utxo.getKey()] = utxo;
}

void Blockchain::spendUTXO(const std::string& txId, int outputIndex) {
    std::string key = txId + ":" + std::to_string(outputIndex);
    if (utxoPool.find(key) != utxoPool.end()) {
        utxoPool[key].markAsSpent();
    }
}

std::vector<UTXO> Blockchain::getUTXOsForAddress(const std::string& address) {
    std::vector<UTXO> result;
    for (const auto& pair : utxoPool) {
        const UTXO& utxo = pair.second;
        if (utxo.getOwner() == address && !utxo.isSpent()) {
            result.push_back(utxo);
        }
    }
    return result;
}

bool Blockchain::validateTransaction(const Transaction& transaction) {
    double inputSum = 0.0;
    double outputSum = 0.0;
    
    // 验证所有输入UTXO
    for (const auto& input : transaction.getInputs()) {
        std::string key = input.first + ":" + std::to_string(input.second);
        if (utxoPool.find(key) == utxoPool.end()) {
            std::cout << "Invalid input UTXO: " << key << std::endl;
            return false;
        }
        
        const UTXO& utxo = utxoPool[key];
        if (utxo.isSpent()) {
            std::cout << "UTXO already spent: " << key << std::endl;
            return false;
        }
        
        if (utxo.getOwner() != transaction.getSender()) {
            std::cout << "UTXO owner mismatch" << std::endl;
            return false;
        }
        
        inputSum += utxo.getAmount();
    }
    
    // 计算输出总和
    for (const auto& output : transaction.getOutputs()) {
        outputSum += output.second;
    }
    
    // 验证输入大于等于输出
    if (inputSum < outputSum) {
        std::cout << "Insufficient funds" << std::endl;
        return false;
    }
    
    return true;
} 