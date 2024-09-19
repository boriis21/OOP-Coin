#ifndef OOPCOIN_USERSARRAY_H
#define OOPCOIN_USERSARRAY_H
#include "User.h"
#include <fstream>

class UsersArray {
public:
    UsersArray();
    UsersArray(const UsersArray&);
    ~UsersArray();
    UsersArray& operator=(const UsersArray&);

    //METHODS
    void push(const User&);
    void removeUser(const char*);
    unsigned getSize() const;

    //OPERATORS
    const User& operator[](const unsigned) const;
    User& operator[](const unsigned);

    friend std::ostream& operator<<(std::ostream&, const UsersArray&);

private:
    User* userArr;
    int size;
    int capacity;

    //HELPERS
    void deallocate();
    void copy(const UsersArray&);

};

#endif //OOPCOIN_USERSARRAY_H
