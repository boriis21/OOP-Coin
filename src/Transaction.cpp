#include "Transaction.h"

void createTransaction(Transaction& transaction, const unsigned senderId, const unsigned receiverId, const double coins) {
    transaction.sender = senderId;
    transaction.receiver = receiverId;
    transaction.time = time(nullptr);
    transaction.coins = coins;
}