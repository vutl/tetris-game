#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "AccountManager.h"

class FriendsAccount {
protected:
    std::vector<std::string> friends;
public:
    virtual ~FriendsAccount() = default;

    virtual void displayFriends() const = 0;
    virtual void addFriend(std::string& friendUsername, AccountManager& accountManager) = 0;
    virtual void sharePoints(std::string& friendUsername, int points, AccountManager& accountManager) = 0;

};