#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include "game.h"
#include "colors.h"
#include "Account.h"
#include "AccountManager.h"

using namespace std;

// Forward declarations
void displayMainMenu();
void displayLoginMenu(Account& account);
void playTetris(Account& account);

double lastUpdateTime = 0;

bool EventTrigerred(double interval)
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
                Account* account = accountManager.findAccount(username, password);
                if (account != nullptr) {
                    displayLoginMenu(*account);
                } else {
                    cout << "Invalid username or password.\n";
                }
                break;
            }
            case '2': {
                string username, password;
                cout << "\nEnter desired username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                accountManager.createAccount(username, password);
                break;
            }
            case '3':
                accountManager.displayAccounts();
                break;
            case '4':
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != '4');

    return 0;
}

void displayMainMenu() {
    cout << "\n=== Main Menu ===\n";
    cout << "1. Login\n";
    cout << "2. Create Account\n";
    cout << "3. Display Accounts\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

void displayLoginMenu(Account& account) {
    char choice;

    do {
        cout << "\n=== Welcome, " << account.getUsername() << " ===\n";
        cout << "1. Play Tetris\n";
        cout << "2. Display Score\n";
        cout << "3. Logout\n";
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
                cout << "Logging out.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != '3');
}

void playTetris(Account& account) {
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();
    game.score = 0;

    while(WindowShouldClose() == false) 
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        if (EventTrigerred(0.2))
        {
            game.MoveBlockDown();
        }
        
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, RED);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();
        EndDrawing();
    }
    account.updateScore(game.score);
    CloseWindow();
}

