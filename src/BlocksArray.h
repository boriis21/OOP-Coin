#ifndef OOPCOIN_BLOCKSARRAY_H
#define OOPCOIN_BLOCKSARRAY_H
#include "TransactionBlock.h"

class BlocksArray {
public:
    //RULE OF 3 + CONSTRUCTORS
    BlocksArray();
    BlocksArray(const BlocksArray&);
    ~BlocksArray();
    BlocksArray& operator=(const BlocksArray&);

    //METHODS
    void push(const TransactionBlock&);
    unsigned getSize() const;

    //OPERATORS
    const TransactionBlock& operator[](const unsigned) const;
    TransactionBlock& operator[](const unsigned);

    friend std::ostream& operator<<(std::ostream&, const BlocksArray&);

private:
    TransactionBlock* blockArr;
    int size;
    int capacity;

    //HELPERS
    void deallocate();
    void copy(const BlocksArray&);
};

#endif //OOPCOIN_BLOCKSARRAY_H
