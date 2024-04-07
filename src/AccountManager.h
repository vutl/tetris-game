#pragma once
#include "Account.h"
#include <vector>

class AccountManager {
private:
    std::vector<Account> accounts;

public:
    void createAccount(const std::string& username, const std::string& password);
    Account* findAccount(const std::string& username, const std::string& password);
    void displayAccounts() const;
};