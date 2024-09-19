#include "UsersArray.h"
#include <iostream>
#include <cstring>
#include <cassert>

//HELPERS
void UsersArray::copy(const UsersArray& other) {
    userArr = new User[other.capacity];
    for (int i = 0; i < other.size; i++) {
        userArr[i] = other.userArr[i];
    }
    capacity = other.capacity;
    size = other.size;
}

void UsersArray::deallocate() {
    delete[] userArr;
}


//RULE OF 3 + CONSTRUCTORS
UsersArray::UsersArray() : size(0), capacity(1) {
    userArr = new (std::nothrow) User[capacity];
    if (!userArr) {
        deallocate();
        std::cerr << "Problem while creating new array in default constructor";
        return;
    }
}

UsersArray::UsersArray(const UsersArray& other) {
    copy(other);
}

UsersArray::~UsersArray() {
    deallocate();
}

UsersArray& UsersArray::operator=(const UsersArray& other) {
    if (&other == this)
        return *this;
    deallocate();
    copy(other);
    return *this;
}


//METHODS
void UsersArray::push(const User& user) {
    if (size < capacity) {
        userArr[size++] = user;
    } else {
        capacity *= 2;
        User* newArray = new (std::nothrow) User[capacity];
        if (!newArray) {
            std::cerr << "Problem while creating new array in push";
            return;
        }
        for (int i = 0; i < size; i++) {
            newArray[i] = userArr[i];
        }
        delete[] userArr;
        userArr = newArray;
        userArr[size++] = user;
    }
}

void UsersArray::removeUser(const char name[128]) {
    bool flag = false;
    for (int i = 0; i < size; i++) {
        if (strcmp(name, userArr[i].name) == 0) {
            flag = true;
            for (int j = i; j < size - 1; j++) {
                userArr[j] = userArr[j + 1];
            }
        }
    }
    size--;

    if (flag)
        std::cout << "The user was removed successfully!" << std::endl;
    else
        std::cout << "There is no user with that name!" << std::endl;
}

unsigned UsersArray::getSize() const {
    return size;
}


//OPERATORS
std::ostream& operator<<(std::ostream& out, const UsersArray& obj) {
    for (int i = 1; i < obj.size; i++) {
        out << obj.userArr[i].id << " " << obj.userArr[i].name << std::endl;
    }

    return out;
}

const User& UsersArray::operator[](const unsigned index) const {
    assert(index >= 0);
    assert(index < size);
    return userArr[index];

}

User& UsersArray::operator[](const unsigned index)  {
    assert(index >= 0);
    assert(index < size);
    return userArr[index];
}