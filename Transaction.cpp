#include "Transaction.h"
#include <ctime>

Transaction::Transaction(const std::string& from, const std::string& to, double value)
    : sender(from), recipient(to), amount(value) {
    timestamp = time(nullptr);
} 