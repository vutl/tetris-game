#include "Account.h"

Account::Account(std::string u, std::string p, std::string t) : username(u), password(p), score(0), type(t) {}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getPassword() const {
    return password;
}

int Account::getScore() const {
    return score;
}

std::string Account::getType() const {
    return type;
}

void Account::updateScore(int points) {
    score += points;
}
