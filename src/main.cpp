#include <iostream>
#include <string>
#include <raylib.h>
#include "game.h"
#include "colors.h"
#include "AccountManager.h"
#include "UserAccount.h"

using namespace std;

void displayMainMenu();
void displayLoginMenu(Account& account);
void playTetris(Account& account);
void displayUserLoginMenu(Account& account, AccountManager& accountManager);
void displayAdminLoginMenu(Account& account, AccountManager& accountManager);
void displayLoginMenu(Account& account, AccountManager& accountManager);

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() {
    AccountManager accountManager;
    accountManager.loadAccounts("accounts.txt");

    char choice;

    do {
        displayMainMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case '1': {
                string username, password;
                cout << "\nEnter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                Account* account = accountManager.findAccount(username);
                if (account != nullptr) {
                    displayLoginMenu(*account, accountManager);
                } else {
                    cout << "Invalid username or password.\n";
                }
                break;
            }
            case '2': {
                string type, username, password;
                do {
                    cout << "\nEnter account type (User, Admin): ";
                    getline(cin, type);
                    cout << "Invalid account type: " << endl;
                } while (type != "User" && type != "Admin" && type != "admin" && type != "user" );
                cout << "Enter desired username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                if (type == "User" || type == "user") {
                    type = "User";
                }
                else if (type == "Admin" || type == "admin") {
                    type = "Admin";
                }
                accountManager.createAccount(type, username, password);
                break;
            }
            case '3':
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != '3');

    accountManager.saveAccounts("accounts.txt");

    return 0;
}

void displayMainMenu() {
    cout << "\n=== Main Menu ===\n";
    cout << "1. Login\n";
    cout << "2. Create Account\n";
    cout << "3. Exit\n";
    cout << "Choose an option: ";
}

void displayLoginMenu(Account& account, AccountManager& accountManager) {
    if (account.getType() == "user") {
                        displayUserLoginMenu(account, accountManager);
                    } else if (account.getType() == "admin") {
                        displayAdminLoginMenu(account, accountManager);
    }
}

void displayUserLoginMenu(Account& account, AccountManager& accountManager) {
    UserAccount* userAccount = dynamic_cast<UserAccount*>(&account);
    string friendUsername;
    int points;
    char choice;
    do {
        cout << "\n=== Welcome, " << account.getUsername() << " ===\n";
        cout << "Choose an option:\n";
        cout << "1. Play Tetris\n";
        cout << "2. Display Score\n";
        cout << "3. Display Friends\n";
        cout << "4. Add Friend\n";
        cout << "5. Share Points\n";
        cout << "6. Logout\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case '1':
                playTetris(account);
                break;
            case '2':
                cout << "Your score: " << account.getScore() << endl;
                break;
            case '3':
                if (userAccount) {
                    userAccount->displayFriends();
                }
                break;
            case '4':
                cout << "Enter friend's username: ";
                cin >> friendUsername;
                if (userAccount) {
                    userAccount->addFriend(friendUsername, accountManager);
                }
                break;
            case '5':
                cout << "Enter friend's username: ";
                cin >> friendUsername;
                cout << "Enter points to share: ";
                cin >> points;
                if (userAccount) {
                    userAccount->sharePoints(friendUsername, points, accountManager);
                }
                break;
            case '6':
                cout << "Logging out.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != '6');
}

void displayAdminLoginMenu(Account& account, AccountManager& accountManager) {
    char choice;
    string usernameToDelete;
    do {
        cout << "\n=== Welcome, " << account.getUsername() << " (Admin) ===\n";
        cout << "Choose an option:\n";
        cout << "1. Play Tetris\n";
        cout << "2. Display Score\n";
        cout << "3. View All Accounts\n";
        cout << "4. Delete Account\n";
        cout << "5. Logout\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case '1':
                playTetris(account);
                break;
            case '2':
                cout << "Your score: " << account.getScore() << endl;
                break;
            case '3':
                accountManager.displayAccounts();
                break;
            case '4':
                cout << "Enter username to delete: ";
                cin >> usernameToDelete;
                accountManager.deleteAccount(usernameToDelete, "admin");
                break;
            case '5':
                cout << "Logging out.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != '5');
}

void playTetris(Account& account) {
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();
    game.score = 0;

    while (WindowShouldClose() == false) {
        UpdateMusicStream(game.music);
        game.HandleInput();
        if (EventTriggered(0.2)) {
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.gameOver) {
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, RED);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();
        EndDrawing();
    }
    account.updateScore(game.score);
    CloseWindow();
}
