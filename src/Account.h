#pragma once
#include <string>

class Account {
private:
    std::string username;
    std::string password;
    int score;
public:
    Account(std::string u, std::string p);
    std::string getUsername() const;
    std::string getPassword() const;
    int getScore() const;
    void updateScore(int points);
};
