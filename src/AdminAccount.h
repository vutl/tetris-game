#pragma once
#include "Account.h"
#include <vector>

class AdminAccount : public Account {
public:
    AdminAccount(std::string u, std::string p);
    void saveToFile(std::ostream& os) const override;
    void loadFromFile(std::istream& is) override;
};
