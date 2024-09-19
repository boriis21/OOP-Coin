#include <iostream>
#include <cstring>
#include "functions.h"

int main() {
    UsersArray users;
    BlocksArray blocks;

    std::cout << "### Welcome to OOPCoin! ###\n\n" ;

    if (checkForUsers()) {
        readUser(users);
        std::cout << "Here is a list of the users in the system: " << std::endl;
        std::cout << users;
    }

    else {
        std::cout << "No Users.dat file found..." << std::endl;

        User system;
        system.id = 0;
        strcpy(system.name, "System User");
        users.push(system);
        writeUser(users);

        std::cout << "Users.dat file was created!" << std::endl;
        std::cout << "System user created!" << std::endl;
    }

    std::cout << std::endl;

    if (checkForBlocks()) {
        readBlocks(blocks);
    }

    else {
        TransactionBlock firstBlock;
        initialize(firstBlock, 0, 0, 0);
        blocks.push(firstBlock);
        std::cout << "No Blocks.dat file found..." << std::endl;
        std::cout << "Blocks.dat file was created!" << std::endl;
    }

    std::cout << "If you want to see all commands you can type \"help\".\n";

    while (true) {
        char command[25];
        std::cout << "\nEnter a command: ";
        std::cin >> command;
        if (strcmp(command, "create-user") == 0)
            createUser(blocks, users);
        else if(strcmp(command, "remove-user") == 0)
            removeUser(blocks, users);
        else if(strcmp(command, "send-coins") == 0)
            sendCoins(blocks, users);
        else if(strcmp(command, "check-balance") == 0)
            checkBalance(blocks, users);
        else if(strcmp(command, "print-users") == 0)
            std::cout << users;
        else if(strcmp(command, "print-transactions") == 0)
            std::cout << blocks;
        else if(strcmp(command, "verify-transactions") == 0)
            verifyTransactions(blocks);
        else if(strcmp(command, "wealthiest-users") == 0) {
            unsigned n;
            std::cout << "Enter how many of the top wealthiest users you want to see: ";
            std::cin >> n;
            wealthiestUsers(blocks, users, n);
        }
        else if(strcmp(command, "biggest-blocks") == 0) {
            unsigned n;
            std::cout << "Enter how many of the top biggest blocks you want to see: ";
            std::cin >> n;
            biggestBlocks(blocks, n);
        }
        else if(strcmp(command, "help") == 0)
            help();
        else if(strcmp(command, "exit") == 0)
            break;
        else
            std::cout << "Invalid command!" << std::endl;
    }

    return 0;
}