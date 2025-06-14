#include "Transaction.h"
#include <ctime>
#include <sstream>
#include <openssl/sha.h>
#include <iomanip>

Transaction::Transaction(const std::string& from, const std::string& to, double value)
    : sender(from), recipient(to), amount(value) {
    timestamp = time(nullptr);
    calculateTransactionId();
}

void Transaction::addInput(const std::string& txId, int outputIndex) {
    inputs.push_back({txId, outputIndex});
}

void Transaction::addOutput(const std::string& recipient, double amount) {
    outputs.push_back({recipient, amount});
}

void Transaction::calculateTransactionId() {
    std::stringstream ss;
    ss << sender << recipient << amount << timestamp;
    
    // Add inputs
    for(const auto& input : inputs) {
        ss << input.first << input.second;
    }
    
    // Add outputs
    for(const auto& output : outputs) {
        ss << output.first << output.second;
    }
    
    std::string input = ss.str();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream hashStream;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hashStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    
    transactionId = hashStream.str();
} 