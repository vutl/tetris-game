#pragma once
#include "Account.h"
#include "UserAccount.h"
#include "AdminAccount.h"
#include <vector>
#include <string>
#include <fstream>

class AccountManager {
private:
    std::vector<Account*> accounts;

    Account* createAccountFromType(const std::string& type, const std::string& username, const std::string& password);

public:
    ~AccountManager();
    void createAccount(const std::string& type, const std::string& username, const std::string& password);
    Account* findAccount(const std::string& username, const std::string& password);
    void displayAccounts() const;
    void deleteAccount(const std::string& username, const std::string& requestingUserType);

    void saveAccounts(const std::string& filename) const;
    void loadAccounts(const std::string& filename);
};
