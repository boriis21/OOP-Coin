#ifndef OOPCOIN_FUNCTIONS_H
#define OOPCOIN_FUNCTIONS_H

#include "UsersArray.h"
#include "TransactionBlock.h"
#include "BlocksArray.h"

//WRITE AND READ FUNCTIONS FOR USERS
void writeUser(const UsersArray&);
void rewriteUser(const UsersArray&);
void readUser(UsersArray&);
bool checkForUsers();


//WRITE AND READ FUNCTIONS FOR BLOCKS
void writeBlocks(const BlocksArray&);
void readBlocks(BlocksArray&);
bool checkForBlocks();


//COMMANDS
void createUser(BlocksArray&, UsersArray&);
void removeUser(BlocksArray&, UsersArray&);
void sendCoins(BlocksArray&, const UsersArray&);
void checkBalance(const BlocksArray&, const UsersArray&);
void verifyTransactions(const BlocksArray&);
void wealthiestUsers(const BlocksArray&, const UsersArray&, const unsigned);
void biggestBlocks(const BlocksArray&, const unsigned);
void help();


//HELPING FUNCTIONS FOR COMMANDS
unsigned findUserIndexByName(const UsersArray&, const char*);
unsigned findUserIndex(const UsersArray& users, const unsigned userId);
void pushTransaction(TransactionBlock&, const Transaction&);
void addTransactionToBlocksArray(BlocksArray&, const Transaction&);
double calculateBalance(const BlocksArray&, const UsersArray&, const unsigned);
double calculateCoinsInBlock(const BlocksArray&, const unsigned);
void sortUsers(const BlocksArray&, UsersArray&);
void sortBlocks(BlocksArray&);
void generateWealthiestUserFileName(char*);
void generateBiggestBlockFileName(char*);

#endif //OOPCOIN_FUNCTIONS_H
