#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <map>

class Transaction {
private:
    std::string transactionId;
    std::string sender;
    std::string recipient;
    double amount;
    time_t timestamp;
    
    // UTXO inputs and outputs
    std::vector<std::pair<std::string, int>> inputs;  // <transactionId, outputIndex>
    std::vector<std::pair<std::string, double>> outputs;  // <recipient, amount>

public:
    Transaction(const std::string& from, const std::string& to, double value);
    
    // 添加输入UTXO
    void addInput(const std::string& txId, int outputIndex);
    
    // 添加输出UTXO
    void addOutput(const std::string& recipient, double amount);
    
    // 计算交易ID
    void calculateTransactionId();
    
    // Getters
    std::string getTransactionId() const { return transactionId; }
    std::string getSender() const { return sender; }
    std::string getRecipient() const { return recipient; }
    double getAmount() const { return amount; }
    time_t getTimestamp() const { return timestamp; }
    const std::vector<std::pair<std::string, int>>& getInputs() const { return inputs; }
    const std::vector<std::pair<std::string, double>>& getOutputs() const { return outputs; }
};

#endif 