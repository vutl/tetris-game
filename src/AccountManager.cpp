#include "AccountManager.h"
#include <iostream>

void AccountManager::createAccount(const std::string& username, const std::string& password) {
    accounts.push_back(Account(username, password));
    std::cout << "Account created successfully.\n";
}

Account* AccountManager::findAccount(const std::string& username, const std::string& password) {
    for (Account& account : accounts) {
        if (account.getUsername() == username && account.getPassword() == password) {
            return &account;
        }
    }
    return nullptr;
}

void AccountManager::displayAccounts() const {
    std::cout << "\n=== Accounts ===\n";
    if (accounts.empty()) {
        std::cout << "No accounts to display.\n";
    } else {
        for (const Account& account : accounts) {
            std::cout << "Username: " << account.getUsername() << ", Score: " << account.getScore() << std::endl;
        }
    }
}
