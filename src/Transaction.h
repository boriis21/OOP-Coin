#ifndef OOPCOIN_TRANSACTION_H
#define OOPCOIN_TRANSACTION_H
#include "UsersArray.h"

struct Transaction {
    unsigned sender;
    unsigned receiver;
    double coins;
    long long time;
};

void createTransaction(Transaction&, const unsigned, const unsigned, const double);

#endif //OOPCOIN_TRANSACTION_H
