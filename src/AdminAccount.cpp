#include "AdminAccount.h"
#include <algorithm>

AdminAccount::AdminAccount(std::string u, std::string p) : Account(u, p, "admin") {}

void AdminAccount::saveToFile(std::ostream& os) const {
    os << "Admin " << username << " " << password << " " << score << "\n";
}

void AdminAccount::loadFromFile(std::istream& is) {
    is >> username >> password >> score;
}
