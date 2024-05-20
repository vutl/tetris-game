#pragma once
#include <string>
#include <iostream>

class Account {
protected:
    std::string username;
    std::string password;
    int score;
    std::string type;

public:
    Account(std::string u, std::string p, std::string t);
    virtual ~Account() = default;

    virtual std::string getUsername() const;
    virtual std::string getPassword() const;
    virtual int getScore() const;
    virtual std::string getType() const; 
    virtual void updateScore(int points);

    virtual void saveToFile(std::ostream& os) const = 0;
    virtual void loadFromFile(std::istream& is) = 0;
};
