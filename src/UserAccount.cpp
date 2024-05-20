#include "UserAccount.h"

UserAccount::UserAccount(std::string u, std::string p) : Account(u, p, "user") {}

void UserAccount::saveToFile(std::ostream& os) const {
    os << "UserAccount " << username << " " << password << " " << score << "\n";
}

void UserAccount::loadFromFile(std::istream& is) {
    is >> username >> password >> score;
}
