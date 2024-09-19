#include "BlocksArray.h"
#include <iostream>
#include <cassert>

//HELPERS
void BlocksArray::copy(const BlocksArray& other) {
    blockArr = new TransactionBlock[other.capacity];
    for (int i = 0; i < other.size; i++) {
        blockArr[i] = other.blockArr[i];
    }
    capacity = other.capacity;
    size = other.size;
}

void BlocksArray::deallocate() {
    delete[] blockArr;
}


//RULE OF 3 + CONSTRUCTORS
BlocksArray::BlocksArray() : size(0), capacity(1){
    blockArr = new (std::nothrow) TransactionBlock[capacity];
    if (!blockArr) {
        deallocate();
        std::cerr << "Problem while creating new blocks array in default constructor...";
        return;
    }
}

BlocksArray::BlocksArray(const BlocksArray& other) {
    copy(other);
}

BlocksArray::~BlocksArray() {
    deallocate();
}

BlocksArray& BlocksArray::operator=(const BlocksArray& other) {
    if (&other == this)
        return *this;
    deallocate();
    copy(other);
    return *this;
}


//METHODS
void BlocksArray::push(const TransactionBlock& block) {
    if (size < capacity) {
        blockArr[size++] = block;
    } else {
        capacity *= 2;
        TransactionBlock* newBlockArr = new (std::nothrow) TransactionBlock[capacity];
        if (!newBlockArr) {
            std::cerr << "Problem while creating new blocks array in push...";
            return;
        }
        for (int i = 0; i < size; i++) {
            newBlockArr[i] = blockArr[i];
        }
        delete[] blockArr;
        blockArr = newBlockArr;
        blockArr[size++] = block;
    }
}

unsigned BlocksArray::getSize() const {
    return size;
}


//OPERATORS
std::ostream& operator<<(std::ostream& out, const BlocksArray& obj) {
    for (int i = 0; i < obj.size; i++) {
        out << "ID: " << obj.blockArr[i].id << std::endl
        << "Previous block ID: " << obj.blockArr[i].prevBlockId << std::endl
        << "Previous block Hash: " << obj.blockArr[i].prevBlockHash << std::endl
        << "Valid transactions: " << obj.blockArr[i].validTransactions << std::endl;
        for (int j = 0; j < obj.blockArr[i].validTransactions; ++j) {
            std::cout << "Transaction #" << j + 1 << ": " << std::endl;
            std::cout << "User #" << obj.blockArr[i].transactions[j].sender << " sent "
            << obj.blockArr[i].transactions[j].coins << " OOPCoins"
             << " to " << "User #" << obj.blockArr[i].transactions[j].receiver <<std::endl;
            std::cout << "Timestamp: " << obj.blockArr[i].transactions[j].time << std::endl;
            std::cout << std::endl;
        }
    }

    return out;
}

const TransactionBlock& BlocksArray::operator[](const unsigned index) const {
    assert(index >= 0);
    assert(index < size);
    return blockArr[index];

}

TransactionBlock& BlocksArray::operator[](const unsigned index)  {
    assert(index >= 0);
    assert(index < size);
    return blockArr[index];
}