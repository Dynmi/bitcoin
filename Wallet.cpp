#include "Wallet.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

Wallet::Wallet() : balance(0.0) {
    // Generate a simple public key (in a real system, this would be a proper cryptographic key pair)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    const char* hex = "0123456789abcdef";
    
    std::stringstream ss;
    for(int i = 0; i < 64; i++) {
        ss << hex[dis(gen)];
    }
    publicKey = ss.str();
}

void Wallet::addTransaction(const Transaction& transaction) {
    transactionHistory.push_back(transaction);
}

void Wallet::updateBalance(double amount) {
    balance += amount;
} 