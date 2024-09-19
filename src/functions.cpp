#include "functions.h"
#include <iostream>
#include <fstream>
#include <cstring>

//WRITE AND READ FUNCTIONS FOR USERS
void writeUser(const UsersArray& users) {
    std::ofstream f("users.dat", std::ios::out | std::ios::binary | std::ios::app);
    if (!f) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    for (int i = 0; i < users.getSize(); i++) {
        f.write(reinterpret_cast<const char*>(&users[i]), sizeof(User));
    }

    f.close();
}

void rewriteUser(const UsersArray& users) {
    std::ofstream f("users.dat", std::ios::out | std::ios::binary);
    if (!f) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    for (int i = 0; i < users.getSize(); i++) {
        f.write(reinterpret_cast<const char*>(&users[i]), sizeof(User));
    }

    f.close();
}

void readUser(UsersArray& users) {
    std::ifstream f("users.dat", std::ios::in | std::ios::binary);
    if (!f) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    User user{};
    while (f.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        users.push(user);
    }

    f.close();
}

bool checkForUsers() {
    std::ifstream file("users.dat", std::ios::in | std::ios::binary);

    if (!file) {
        return false;
    }

    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.close();

    if (fileSize != 0 && fileSize % sizeof(User) == 0) {
        return true;
    }

    return false;
}



//WRITE AND READ FUNCTIONS FOR BLOCKS
void writeBlocks(const BlocksArray& blocks) {
    std::ofstream f("blocks.dat", std::ios::out | std::ios::binary);
    if (!f) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    for (int i = 0; i < blocks.getSize(); i++) {
        f.write(reinterpret_cast<const char*>(&blocks[i]), sizeof(TransactionBlock));
    }

    f.close();
}

void readBlocks(BlocksArray& blocks) {
    std::ifstream f("blocks.dat", std::ios::in | std::ios::binary);
    if (!f) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    TransactionBlock block{};
    while (f.read(reinterpret_cast<char*>(&block), sizeof(TransactionBlock))) {
        blocks.push(block);
    }

    f.close();
}

bool checkForBlocks() {
    std::ifstream file("blocks.dat", std::ios::in | std::ios::binary);

    if (!file) {
        return false;
    }

    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.close();

    if (fileSize != 0 && fileSize % sizeof(TransactionBlock) == 0) {
        return true;
    }

    return false;
}



//COMMANDS
void createUser(BlocksArray& blocks, UsersArray& users) {
    char name[128];
    double investment;

    std::cout << "Enter user name : ";
    std::cin.ignore(sizeof(name), '\n');
    std::cin.getline(name, sizeof(name));
    std::cout << "Enter the amount of money you will invest: ";
    std::cin >> investment;

    if (investment <= 0) {
        std::cout << "You cannot invest money below 0!" << std::endl;
        return;
    }

    User user{};
    UsersArray tempUsers;
    readUser(tempUsers);
    unsigned startID = tempUsers[tempUsers.getSize() - 1].id + 1;
    initialize(user, startID, name);
    users.push(user);

    rewriteUser(users);

    Transaction transaction{};
    createTransaction(transaction, users[0].id, users[users.getSize() - 1].id, investment * 420);

    addTransactionToBlocksArray(blocks, transaction);
    writeBlocks(blocks);
}

void removeUser(BlocksArray& blocks, UsersArray& users) {
    char nameToRem[128];
    std::cout << "Enter the name of the user you want to remove: ";
    std::cin.ignore(sizeof(nameToRem), '\n');
    std::cin.getline(nameToRem, sizeof(nameToRem));

    unsigned userToRemoveIndex = findUserIndexByName(users, nameToRem);
    if (userToRemoveIndex == -1) {
        std::cout << "No user with that name found!" << std::endl;
        return;
    }

    if (strcmp(nameToRem, "System_User") == 0) {
        std::cout << "You cannot remove the system user!" << std::endl;
    }
    else {
        Transaction transaction{};
        createTransaction(transaction, userToRemoveIndex, users[0].id, calculateBalance(blocks, users, userToRemoveIndex));
        addTransactionToBlocksArray(blocks, transaction);
        writeBlocks(blocks);

        users.removeUser(nameToRem);
        rewriteUser(users);
    }
}

void sendCoins(BlocksArray& blocks, const UsersArray& users) {
    unsigned senderId;
    std::cout << "Enter the ID of the sender: ";
    std::cin >> senderId;

    unsigned receiverId;
    std::cout << "Enter the ID of the receiver: ";
    std::cin >> receiverId;

    double coins;
    std::cout << "Enter the amount of coins you want to send: ";
    std::cin >> coins;

    if (coins <= 0) {
        std::cout << "You cannot send money below or equal to 0!" << std::endl;
        return;
    }

    unsigned sender = findUserIndex(users, senderId);
    if (sender == -1) {
        std::cout << "Invalid id for sender!" << std::endl;
        return;
    }

    unsigned receiver = findUserIndex(users, receiverId);
    if (receiver == -1) {
        std::cout << "Invalid id for receiver!" << std::endl;
        return;
    }

    if (sender == 0 || receiver == 0) {
        std::cout << "You cannot make transactions with the system user!" << std::endl;
        return;
    }

    if (sender == receiver) {
        std::cout << "Sender and receiver cannot be the same!" << std::endl;
        return;
    }

    double senderBalance = calculateBalance(blocks, users, senderId);
    if (senderBalance < coins) {
        std::cout << "User #" << senderId << " does not have enough funds to make this transaction!" << std::endl;
        return;
    }
    else {
        Transaction transaction{};
        createTransaction(transaction, senderId, receiverId, coins);
        addTransactionToBlocksArray(blocks, transaction);
        writeBlocks(blocks);
        std::cout << "The transaction was successful!" << std::endl;
    }
}

void checkBalance(const BlocksArray& blocks, const UsersArray& users) {
    unsigned id = 0;
    std::cout << "Enter the ID of the user whose balance you want to check: ";
    std::cin >> id;
    if (id <= 0) {
        std::cout << "Invalid ID!" << std::endl;
        return;
    }
    std::cout << "The balance of user #" << id << " is: " << calculateBalance(blocks, users, id) << std::endl;
}

void verifyTransactions(const BlocksArray& blocks) {
    bool isValid = true;

    if (blocks[0].validTransactions == 0)
        isValid = false;

    for (int i = 1; i < blocks.getSize(); ++i) {
        if (blocks[i].prevBlockHash != computeHash(reinterpret_cast<const unsigned char*>(&blocks[i - 1]), sizeof(blocks[i - 1])) &&
        blocks[i].prevBlockId != blocks[i - 1].id && blocks[i].validTransactions == 0)
            isValid = false;
    }

    if (isValid) {
        std::cout << "The transactions were verified!" << std::endl;
        return;
    }
    else {
        std::cout << "The transaction blocks chain is broken!" << std::endl;
        return;
    }
}

void wealthiestUsers(const BlocksArray& blocks, const UsersArray& users, const unsigned n) {
    UsersArray sortedUsers = users;
    sortUsers(blocks, sortedUsers);
    if (n >= sortedUsers.getSize()) {
        std::cout << "There are not that many users in the system!" << std::endl;
        return;
    }

    char* fileName = new (std::nothrow) char[50];
    if (!fileName) {
        std::cout << "Problem while allocating memory!" << std::endl;
        return;
    }
    generateWealthiestUserFileName(fileName);

    std::ofstream f(fileName);
    if (!f) {
        std::cout << "Problem opening the text file to write the wealthiest users!" << std::endl;
        return;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << i + 1 << ". " << sortedUsers[i].name << " with " << calculateBalance(blocks, users, sortedUsers[i].id) << " OOPCoins." << std::endl;
        f << i + 1 << ". " << sortedUsers[i].name << " with " << calculateBalance(blocks, users, sortedUsers[i].id) << " OOPCoins." << std::endl;
    }
    std::cout << std::endl << n << " users were saved in " << fileName << std::endl;

    f.close();
    delete[] fileName;
}

void biggestBlocks(const BlocksArray& blocks, const unsigned n) {
    BlocksArray sortedBlocks = blocks;
    sortBlocks(sortedBlocks);
    if (n > sortedBlocks.getSize()) {
        std::cout << "There are not that many blocks in the system!" << std::endl;
        return;
    }

    char* fileName = new (std::nothrow) char[50];
    if (!fileName) {
        std::cout << "Problem while allocating memory!" << std::endl;
        return;
    }
    generateBiggestBlockFileName(fileName);

    std::ofstream f(fileName);
    if (!f) {
        std::cout << "Problem opening the text file to write the biggest blocks!" << std::endl;
        return;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << i + 1 << ". Block #" << sortedBlocks[i].id << " with total coins: " << calculateCoinsInBlock(blocks, sortedBlocks[i].id) <<std::endl;
        f << i + 1 << ". Block #" << sortedBlocks[i].id << " with total coins : " << calculateCoinsInBlock(blocks, sortedBlocks[i].id) <<std::endl;
    }
    std::cout << std::endl << n << " blocks were saved in " << fileName << std::endl;

    f.close();
    delete[] fileName;
}

void help() {
    std::cout << "Commands: \n"
                 "create-user, \n"
                 "remove-user, \n"
                 "send-coins, \n"
                 "check-balance, \n"
                 "print-users, \n"
                 "print-transactions, \n"
                 "help, \n"
                 "exit" << std::endl;
    std::cout << std::endl;
}



//HELPING FUNCTIONS FOR COMMANDS
unsigned findUserIndexByName(const UsersArray& users, const char name[128]) {
    for (int i = 0; i < users.getSize(); i++) {
        if (strcmp(name, users[i].name) == 0) {
            return users[i].id;
        }
    }
    return -1;
}

unsigned findUserIndex(const UsersArray& users, const unsigned userId) {
    for (int i = 0; i < users.getSize(); i++) {
        if (users[i].id == userId) {
            return users[i].id;
        }
    }
    return -1;
}

void pushTransaction(TransactionBlock& block, const Transaction& transaction) {
    if (block.validTransactions >= 16) {
        std::cout << "This block is full!" << std::endl;
    }

    block.transactions[block.validTransactions++] = transaction;
}

void addTransactionToBlocksArray(BlocksArray& blocks, const Transaction& transaction) {
    unsigned lastBlockIndex = blocks.getSize() - 1;
    if (blocks[lastBlockIndex].validTransactions >= 16) {
        TransactionBlock newBlock{};
        BlocksArray tempBlocks;
        readBlocks(tempBlocks);
        unsigned startID = tempBlocks[tempBlocks.getSize() - 1].id + 1;
        initialize(newBlock, generateBlockId(startID), lastBlockIndex, computeHash(reinterpret_cast<const unsigned char*>(&blocks[lastBlockIndex]), sizeof(blocks[lastBlockIndex])));
        pushTransaction(newBlock, transaction);
        blocks.push(newBlock);
    }
    else
        pushTransaction(blocks[lastBlockIndex], transaction);

}

double calculateBalance(const BlocksArray& blocks, const UsersArray& users, const unsigned userId) {
    double balance = 0;
    unsigned checkId = findUserIndex(users, userId);
    if (checkId == -1) {
        std::cout << "\nInvalid ID! ";
        return 0;
    }

    for (int i = 0; i < blocks.getSize(); ++i) {
        for (int j = 0; j < blocks[i].validTransactions; ++j) {
            if (blocks[i].transactions[j].receiver == userId)
                balance += blocks[i].transactions[j].coins;
            else if (blocks[i].transactions[j].sender == userId)
                balance -= blocks[i].transactions[j].coins;
        }
    }

    return balance;
}

double calculateCoinsInBlock(const BlocksArray& blocks, const unsigned blockID) {
    double totalCoins = 0;
    for (int i = 0; i < blocks[blockID].validTransactions; ++i) {
        totalCoins += blocks[blockID].transactions[i].coins;
    }
    return totalCoins;
}

void sortUsers(const BlocksArray& blocks, UsersArray& users) {
    double balance1, balance2;
    for (int i = 0; i < users.getSize() - 1; ++i) {
        for (int j = 0; j < users.getSize() - i - 1; ++j) {
            balance1 = calculateBalance(blocks, users, users[j].id);
            balance2 = calculateBalance(blocks, users, users[j + 1].id);
            if (balance1 < balance2) {
                User temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }
}

void sortBlocks(BlocksArray& blocks) {
    double total1, total2;
    for (int i = 0; i < blocks.getSize() - 1; ++i) {
        for (int j = 0; j < blocks.getSize() - i - 1; ++j) {
            total1 = 0;
            for (int k = 0; k < blocks[j].validTransactions; ++k) {
                total1 += blocks[j].transactions[k].coins;
            }
            total2 = 0;
            for (int k = 0; k < blocks[j + 1].validTransactions; ++k) {
                total2 += blocks[j + 1].transactions[k].coins;
            }
            if (total1 < total2) {
                TransactionBlock temp = blocks[j];
                blocks[j] = blocks[j + 1];
                blocks[j + 1] = temp;
            }
        }
    }
}

void generateWealthiestUserFileName(char* fileName) {
    sprintf(fileName, "wealthiest_users_%ld.txt", time(nullptr));
}

void generateBiggestBlockFileName(char* fileName) {
    sprintf(fileName, "biggest_block_%ld.txt", time(nullptr));
}