#ifndef OOPCOIN_TRANSACTIONBLOCK_H
#define OOPCOIN_TRANSACTIONBLOCK_H
#include "Transaction.h"

struct TransactionBlock {
    unsigned id;
    unsigned prevBlockId;
    unsigned prevBlockHash;
    int validTransactions;
    Transaction transactions[16];
};

void initialize(TransactionBlock&, const unsigned, const unsigned, const unsigned);
unsigned generateBlockId(const unsigned);
unsigned computeHash(const unsigned char *memory, int length);

#endif //OOPCOIN_TRANSACTIONBLOCK_H
