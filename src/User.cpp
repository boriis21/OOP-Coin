#include "User.h"
#include <cstring>

unsigned generateUserId(const unsigned startFrom) {
    static unsigned uniqueId = startFrom;
    return uniqueId++;
}

void initialize(User& user, const unsigned startFrom, const char name[128]) {
    user.id = generateUserId(startFrom);
    strcpy(user.name, name);
}