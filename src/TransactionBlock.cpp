#include "TransactionBlock.h"

void initialize(TransactionBlock& block, const unsigned ID, const unsigned prevID, const unsigned hash) {
    block.id = ID;
    block.prevBlockId = prevID;
    block.prevBlockHash = hash;
    block.validTransactions = 0;
}

unsigned generateBlockId(const unsigned start) {
    static unsigned uniqueId = start;
    return uniqueId++;
}

unsigned computeHash(const unsigned char *memory, int length) {
    unsigned hash = 0xbeaf;

    for (int c = 0; c < length; c++) {
        hash += memory[c];
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

