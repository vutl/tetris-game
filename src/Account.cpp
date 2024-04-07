#include "Account.h"

Account::Account(std::string u, std::string p) : username(u), password(p), score(0) {}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getPassword() const {
    return password;
}

int Account::getScore() const {
    return score;
}

void Account::updateScore(int points) {
    score += points;
}