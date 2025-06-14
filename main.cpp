#include "Blockchain.h"
#include "Wallet.h"
#include <iostream>

int main() {
    // Create blockchain
    Blockchain bitcoin;
    
    // Create wallets
    Wallet wallet1;
    Wallet wallet2;
    
    std::cout << "Wallet 1 address: " << wallet1.getPublicKey() << std::endl;
    std::cout << "Wallet 2 address: " << wallet2.getPublicKey() << std::endl;
    
    // Mine first block
    std::cout << "\nMining first block..." << std::endl;
    bitcoin.minePendingTransactions(wallet1.getPublicKey());
    
    // Create transaction
    std::cout << "\nCreating transaction..." << std::endl;
    Transaction tx1(wallet1.getPublicKey(), wallet2.getPublicKey(), 50.0);
    bitcoin.addTransaction(tx1);
    
    // Mine second block
    std::cout << "\nMining second block..." << std::endl;
    bitcoin.minePendingTransactions(wallet1.getPublicKey());
    
    // Check balances
    std::cout << "\nWallet 1 balance: " << bitcoin.getBalanceOfAddress(wallet1.getPublicKey()) << std::endl;
    std::cout << "Wallet 2 balance: " << bitcoin.getBalanceOfAddress(wallet2.getPublicKey()) << std::endl;
    
    // Verify blockchain
    std::cout << "\nIs blockchain valid? " << (bitcoin.isChainValid() ? "Yes" : "No") << std::endl;
    
    return 0;
} 