#include "UserAccount.h"
#include "AccountManager.h"

UserAccount::UserAccount(std::string u, std::string p) : Account(u, p, "user"), numFriends(0) {}

void UserAccount::saveToFile(std::ostream& os) const {
    os << "UserAccount " << username << " " << password << " " << score << " ";
    os << friends.size();
    for (const std::string& friendUsername : friends) {
        os << " " << friendUsername;
    }
    os << "\n";
}

void UserAccount::loadFromFile(std::istream& is) {
    is >> username >> password >> score >> numFriends;
    friends.clear();
    for (int i = 0; i < numFriends; ++i) {
        std::string friendUsername;
        is >> friendUsername;
        friends.push_back(friendUsername);
    }
}

void UserAccount::displayFriends() const {
    std::cout << "Friends:\n";
    for (auto& friendUsername : friends) {
        std::cout << friendUsername << std::endl;
    }
}

void UserAccount::addFriend(std::string& friendUsername, AccountManager& accountManager) {
    if (accountManager.findAccount(friendUsername) != nullptr && friendUsername != username) {
        friends.push_back(friendUsername);
        std::cout << "Friend added: " << friendUsername << std::endl;
        this->numFriends++;
        UserAccount* friendAccount = dynamic_cast<UserAccount*>(accountManager.findAccount(friendUsername));
        if (friendAccount) {
            friendAccount->friends.push_back(username);
            std::cout << "You added as a friend to: " << friendUsername << std::endl;
        } else {
            std::cout << "Failed to add yourself as a friend to: " << friendUsername << std::endl;
        }
    } 
    else if (friendUsername == username) {
        std::cout << "Cannot add yourself!\n" << std::endl;
    } else {
        std::cout << "No such account exists.\n";
    }
}

void UserAccount::sharePoints(std::string& friendUsername, int points, AccountManager& accountManager) {
    Account* friendAccount = accountManager.findAccount(friendUsername);
    if (friendAccount && getScore() >= points) {
        updateScore(-points);
        friendAccount->updateScore(points);
        accountManager.saveAccounts("accounts.txt");
        std::cout << "Shared " << points << " points with " << friendUsername << std::endl;
    } else {
        std::cout << "Failed to share points.\n";
    }
}