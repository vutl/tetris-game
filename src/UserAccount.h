#pragma once
#include <iostream>
#include "Account.h"
#include "FriendsAccount.h"

class AccountManager;

class UserAccount : public Account, public FriendsAccount {
public:
    UserAccount(std::string u, std::string p);
    void saveToFile(std::ostream& os) const override;
    void loadFromFile(std::istream& is) override;

    void displayFriends() const override;
    void addFriend(std::string& friendUsername, AccountManager& accountManager) override;
    void sharePoints(std::string& friendUsername, int points, AccountManager& accountManager) override;
};
