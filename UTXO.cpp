#include "UTXO.h"

UTXO::UTXO(const std::string& txId, int index, const std::string& ownerAddr, double value)
    : transactionId(txId), outputIndex(index), owner(ownerAddr), amount(value), spent(false) {} 