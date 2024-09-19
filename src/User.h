#ifndef OOPCOIN_USER_H
#define OOPCOIN_USER_H

struct User {
    unsigned id;
    char name[128];
};

unsigned generateUserId(const unsigned);
void initialize(User& user, const unsigned startFrom, const char name[128]);

#endif //OOPCOIN_USER_H
