#include "UserAccount.h"
#include "AccountManager.h"

UserAccount::UserAccount(std::string u, std::string p) : Account(u, p, "user") {}

void UserAccount::saveToFile(std::ostream& os) const {
    os << "UserAccount " << username << " " << password << " " << score << "\n";
}

void UserAccount::loadFromFile(std::istream& is) {
    is >> username >> password >> score;
}

void UserAccount::displayFriends() const {
    std::cout << "Friends:\n";
    for (const auto& friendUsername : friends) {
        std::cout << friendUsername << std::endl;
    }
}

void UserAccount::addFriend(std::string& friendUsername, AccountManager& accountManager) {
    if (accountManager.findAccount(friendUsername) != nullptr) {
        friends.push_back(friendUsername);
        std::cout << "Friend added: " << friendUsername << std::endl;
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