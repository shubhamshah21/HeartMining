#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

const char HEART = '\3'; // Heart Symbol
const char SPADE = '\6'; // Spade Symbol
const int ROWS = 4;
const int COLS = 6;
char game_grid[ROWS][COLS], card_symbols[ROWS][COLS];
int tries, tot_hearts, found_hearts, total_score, overall_score = 0;
char level, choice;
string difficulty;

void SetColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
    cout << "\033[" << color << "m";
#endif
}

void ResetColor() {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
#else
    cout << "\033[0m";
#endif
}

void SetupGrid() {
    char letter = 'A';
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            game_grid[i][j] = letter++;
            card_symbols[i][j] = SPADE;
        }
    }
}

void PlaceHearts() {
    srand(time(0));
    for (int q = tot_hearts; q > 0; q--) {
        int row, col;
        do {
            row = rand() % ROWS;
            col = rand() % COLS;
        } while (card_symbols[row][col] == HEART);
        card_symbols[row][col] = HEART;
    }
}

void DrawGrid() {
    system("CLS");
    SetColor(11);
    cout << "\n========= HEART MINING GAME =========\n";
    ResetColor();
    cout << "  -------------------------\n";
    for (int i = 0; i < ROWS; i++) {
        cout << "  |";
        for (int j = 0; j < COLS; j++) {
            if (game_grid[i][j] == HEART) SetColor(12);
            else if (game_grid[i][j] == SPADE) SetColor(8);
            cout << " " << game_grid[i][j] << " |";
            ResetColor();
        }
        cout << "\n  -------------------------\n";
    }
    cout << "Hearts found: " << found_hearts << " / " << tot_hearts << "\n";
    cout << "Turns left: " << tries << "\n";
}

void ChooseLevel() {
    do {
        cout << "\nChoose Difficulty:\n";
        cout << "(N) Novice - 20 tries, 13 hearts\n";
        cout << "(F) Fresher - 16 tries, 10 hearts\n";
        cout << "(J) Junior - 12 tries, 7 hearts\n";
        cout << "(E) Expert - 8 tries, 5 hearts\n";
        cout << "Enter choice: ";
        cin >> level;
        switch (tolower(level)) {
            case 'n': tries = 20; tot_hearts = 13; difficulty = "Novice"; break;
            case 'f': tries = 16; tot_hearts = 10; difficulty = "Fresher"; break;
            case 'j': tries = 12; tot_hearts = 7; difficulty = "Junior"; break;
            case 'e': tries = 8; tot_hearts = 5; difficulty = "Expert"; break;
            default: tries = 0; cout << "Invalid choice. Try again.\n";
        }
    } while (tries == 0);
}

void PlayGame() {
    SetupGrid();
    PlaceHearts();
    found_hearts = 0;
    while (tries > 0 && found_hearts < tot_hearts) {
        DrawGrid();
        char choice;
        cout << "Pick a letter: ";
        cin >> choice;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (game_grid[i][j] == choice) {
                    game_grid[i][j] = card_symbols[i][j];
                    if (game_grid[i][j] == HEART) found_hearts++;
                }
            }
        }
        tries--;
    }
    total_score = found_hearts * 100;
    overall_score += total_score;
    DrawGrid();
    cout << (found_hearts == tot_hearts ? "You won!" : "Game Over!") << "\n";
    cout << "Score this round: " << total_score << "\n";
}

int main() {
    do {
        system("CLS");
        SetColor(14);
        cout << "\nWelcome to Heart Mining Game!\n";
        ResetColor();
        ChooseLevel();
        PlayGame();
        cout << "Play again? (Y/N): ";
        cin >> choice;
    } while (tolower(choice) == 'y');
    cout << "\nOverall Score: " << overall_score << "\n";
    return 0;
}

