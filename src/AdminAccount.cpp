#include "AdminAccount.h"
#include <algorithm>

AdminAccount::AdminAccount(std::string u, std::string p) : Account(u, p, "admin") {}

// void AdminAccount::deleteAccount(std::vector<Account*>& accounts, const std::string& usernameToDelete) {
//     accounts.erase(std::remove_if(accounts.begin(), accounts.end(), [&](Account* account) {
//         return account->getUsername() == usernameToDelete;
//     }), accounts.end());
// }

void AdminAccount::saveToFile(std::ostream& os) const {
    os << "AdminAccount " << username << " " << password << " " << score << "\n";
}

void AdminAccount::loadFromFile(std::istream& is) {
    is >> username >> password >> score;
}
