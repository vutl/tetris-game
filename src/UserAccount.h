#pragma once
#include "Account.h"

class UserAccount : public Account {
public:
    UserAccount(std::string u, std::string p);
    void saveToFile(std::ostream& os) const override;
    void loadFromFile(std::istream& is) override;
};
