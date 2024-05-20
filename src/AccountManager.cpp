#include "AccountManager.h"
#include <iostream>
#include <algorithm>
#include "UserAccount.h"

AccountManager::~AccountManager() {
    for (Account* account : accounts) {
        delete account;
    }
}

Account* AccountManager::createAccountFromType(const std::string& type, const std::string& username, const std::string& password) {
    if (type == "UserAccount") {
        return new UserAccount(username, password);
    } else if (type == "AdminAccount") {
        return new AdminAccount(username, password);
    }
    else {
        std::cout << "Invalid choice. Choose again!" << std::endl;
        return nullptr;
    }
}

void AccountManager::createAccount(const std::string& type, const std::string& username, const std::string& password) {
    Account* account = createAccountFromType(type, username, password);
    if (account) {
        accounts.push_back(account);
        std::cout << "Account created successfully.\n";
    } else {
        std::cout << "Failed to create account. Unknown type.\n";
    }
}

Account* AccountManager::findAccount(const std::string& username) {
    for (Account* account : accounts) {
        if (account->getUsername() == username) {
            return account;
        }
    }
    return nullptr;
}

void AccountManager::displayAccounts() const {
    std::cout << "\n=== Accounts ===\n";
    if (accounts.empty()) {
        std::cout << "No accounts to display.\n";
    } else {
        for (const Account* account : accounts) {
            std::cout << "Username: " << account->getUsername() << ", Score: " << account->getScore() << std::endl;
        }
    }
}

void AccountManager::deleteAccount(const std::string& username, const std::string& type) {
    if (type != "admin") {
        std::cout << "Only admin accounts can delete accounts." << std::endl;
        return;
    }
    auto it = std::find_if(accounts.begin(), accounts.end(), [&](Account* acc) {
        return acc->getUsername() == username;
});

    if (it != accounts.end()) {
        delete *it;
        accounts.erase(it);
        std::cout << "Account '" << username << "' deleted successfully." << std::endl;
    } else {
        std::cout << "Account '" << username << "' not found." << std::endl;
    }
}

void AccountManager::saveAccounts(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for saving.\n";
        return;
    }

    for (const Account* account : accounts) {
        account->saveToFile(file);
    }

    file.close();
}

void AccountManager::loadAccounts(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for loading.\n";
        return;
    }

    std::string type;
    while (file >> type) {
        Account* account = createAccountFromType(type, "", "");
        if (account) {
            account->loadFromFile(file);
            accounts.push_back(account);
        }
    }

    file.close();
}
