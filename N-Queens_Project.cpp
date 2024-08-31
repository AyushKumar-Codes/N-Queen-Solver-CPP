#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#define COLOR_BGW   "\x1b[47m"
#define COLOR_BGB   "\x1b[100m"
#define COLOR_BLK   "\x1b[30m"
#define COLOR_RESET "\x1b[0m"

using namespace std;

void continuee() {
    cout << "\n Press [Enter] for another solution.";
    cin.ignore();
    cin.get();
}

void wait(unsigned int secs) {              // Wait x seconds
    unsigned int retTime = time(0) + secs;  // Get finishing time.
    while (time(0) < retTime);              // Loop until it arrives.
}

int color(int i, int j) {
    return (i + j) % 2;
}

int countSLT() {
    static int k = 1;  // Start numbering from 1
    return k++;
}

void printBoard(const vector<vector<int>>& board, bool delay) {
    system("clear");
    int N = board.size();
    if (delay) cout << "\n N-QUEENS (delay=1s)\n\n";
    else cout << "\n N-QUEENS\n\n";
    for (int i = 0; i < N; i++) {
        cout << " " << i + 1 << " ";
        for (int j = 0; j < N; j++) {
            if (!color(i, j)) {
                if (board[i][j])
                    cout << COLOR_BGW << COLOR_BLK << " Q " << COLOR_RESET;
                else
                    cout << COLOR_BGW << "   " << COLOR_RESET;
            }
            else {
                if (board[i][j])
                    cout << COLOR_BGB << COLOR_BLK << " Q " << COLOR_RESET;
                else
                    cout << COLOR_BGB << "   " << COLOR_RESET;
            }
        }
        cout << "\n";
    }
    cout << "   ";
    for (int i = 0; i < N; i++) {
        cout << " " << static_cast<char>(i + 97) << " ";
    }
    if (delay) cout << "\n\n Processing...\n (ctrl+c to abort)\n";
    else cout << "\n";
}

bool valida(const vector<vector<int>>& board, int row, int col) {
    int N = board.size();
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool solve(vector<vector<int>>& board, int col, bool delay, bool &foundSolution) {
    int N = board.size();
    if (col == N) {
        printBoard(board, delay);
        cout << "\n Solution: " << countSLT();
        continuee();
        foundSolution = true;
        return true;
    }

    bool solution = false;
    for (int i = 0; i < N; i++) {
        if (valida(board, i, col)) {
            board[i][col] = 1;
            printBoard(board, delay);
            if (delay) wait(1);
            solution = solve(board, col + 1, delay, foundSolution) || solution;
            board[i][col] = 0;
            printBoard(board, delay);
            if (delay) wait(1);
        }
    }
    return solution;
}

void callNQ() {
    system("clear");
    int N;
    cout << "Enter the number of queens: ";
    cin >> N;
    vector<vector<int>> board(N, vector<int>(N, 0));
    char ask;
    bool delay = false;
    bool foundSolution = false;
    cout << "\n Use the delay to visualize the backtracking? [y/n] ";
    cin >> ask;
    if (ask == 'y') delay = true;
    solve(board, 0, delay, foundSolution);
    if (!foundSolution) {
        cout << "There is no solution\n";
    } else {
        cout << "\n No more solutions.\n";
    }
}

int main() {
    callNQ();
    return 0;
}
