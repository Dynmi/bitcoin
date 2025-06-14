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
    
    // Mine first block to get some initial coins
    std::cout << "\nMining first block..." << std::endl;
    bitcoin.minePendingTransactions(wallet1.getPublicKey());
    
    // Create transaction from wallet1 to wallet2
    std::cout << "\nCreating transaction from wallet1 to wallet2..." << std::endl;
    Transaction tx1(wallet1.getPublicKey(), wallet2.getPublicKey(), 50.0);
    
    // Add input UTXO (from mining reward)
    tx1.addInput(bitcoin.getPendingTransactions()[0].getTransactionId(), 0);
    
    // Add outputs
    tx1.addOutput(wallet2.getPublicKey(), 50.0);  // Payment to wallet2
    tx1.addOutput(wallet1.getPublicKey(), 45.0);  // Change back to wallet1
    
    bitcoin.addTransaction(tx1);
    
    // Mine second block
    std::cout << "\nMining second block..." << std::endl;
    bitcoin.minePendingTransactions(wallet1.getPublicKey());
    
    // Check balances
    std::cout << "\nWallet 1 balance: " << bitcoin.getBalanceOfAddress(wallet1.getPublicKey()) << std::endl;
    std::cout << "Wallet 2 balance: " << bitcoin.getBalanceOfAddress(wallet2.getPublicKey()) << std::endl;
    
    // Print UTXOs for each wallet
    std::cout << "\nUTXOs for Wallet 1:" << std::endl;
    for (const auto& utxo : bitcoin.getUTXOsForAddress(wallet1.getPublicKey())) {
        std::cout << "UTXO: " << utxo.getTransactionId() << ":" << utxo.getOutputIndex() 
                  << " Amount: " << utxo.getAmount() << std::endl;
    }
    
    std::cout << "\nUTXOs for Wallet 2:" << std::endl;
    for (const auto& utxo : bitcoin.getUTXOsForAddress(wallet2.getPublicKey())) {
        std::cout << "UTXO: " << utxo.getTransactionId() << ":" << utxo.getOutputIndex() 
                  << " Amount: " << utxo.getAmount() << std::endl;
    }
    
    // Verify blockchain
    std::cout << "\nIs blockchain valid? " << (bitcoin.isChainValid() ? "Yes" : "No") << std::endl;
    
    return 0;
} 