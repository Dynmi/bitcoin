#include "Block.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>

Block::Block(int idx, const std::string& prevHash, const std::vector<Transaction>& txs)
    : index(idx), previousHash(prevHash), transactions(txs), nonce(0) {
    timestamp = time(nullptr);
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << previousHash << timestamp << nonce;
    
    for(const auto& tx : transactions) {
        ss << tx.getSender() << tx.getRecipient() << tx.getAmount() << tx.getTimestamp();
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
    
    return hashStream.str();
}

void Block::mineBlock(int difficulty) {
    std::string target(difficulty, '0');
    while(hash.substr(0, difficulty) != target) {
        nonce++;
        hash = calculateHash();
    }
    std::cout << "Block mined: " << hash << std::endl;
} 