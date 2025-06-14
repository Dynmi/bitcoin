#ifndef UTXO_H
#define UTXO_H

#include <string>

class UTXO {
private:
    std::string transactionId;  // 产生这个UTXO的交易ID
    int outputIndex;           // 在交易中的输出索引
    std::string owner;         // 拥有者地址
    double amount;             // 金额
    bool spent;                // 是否已花费

public:
    UTXO(const std::string& txId, int index, const std::string& ownerAddr, double value);
    
    // Getters
    std::string getTransactionId() const { return transactionId; }
    int getOutputIndex() const { return outputIndex; }
    std::string getOwner() const { return owner; }
    double getAmount() const { return amount; }
    bool isSpent() const { return spent; }
    
    // Setters
    void markAsSpent() { spent = true; }
    
    // 用于在map中作为key
    std::string getKey() const {
        return transactionId + ":" + std::to_string(outputIndex);
    }
};

#endif 