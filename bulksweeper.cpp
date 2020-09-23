#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include <string>

std::vector<std::vector<int>> populate_board(std::vector<std::vector<int>> board, std::set<int> mine_locs, int height, int width);
std::set<int> rand_combi(int n, int k, std::mt19937 &engine, std::uniform_real_distribution<double> distribution);
void draw_board(std::vector<std::vector<int>> board, std::vector<std::vector<int>> cleared, int height, int width);
bool inside_board(int row, int col, int height, int width);

int main()
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 engine(seed);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    int height;
    int width;
    int num_mines;
    bool board_cleared = false;

    // Get board parameters from user
    std::cout << "Board Height: ";
    std::cin >> height;
    std::cout << "Board Width: ";
    std::cin >> width;
    std::cout << "Number of Mines: ";
    std::cin >> num_mines;
    int tiles = height * width;

    // Initializing board
    // -1 => Mine
    std::vector<std::vector<int>> board = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    // Matrix of cleared cells
    // 0 => Uncleared
    // 1 => Cleared in a try
    // 2 => Confirmed clear (after a try)
    std::vector <std::vector<int>> cleared = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    draw_board(board, cleared, height, width);

    std::string cmd;
    while (!board_cleared) {
        std::cin >> cmd;
        if (cmd == "yes") {
            board_cleared = true;
        }
        draw_board(board, cleared, height, width);
    }
    // std::set<int> mine_locs = rand_combi(tiles, num_mines, engine, distribution);
    // board = populate_board(board, mine_locs, height, width);

}

// Algorithm for sampling without replacement
// https://stackoverflow.com/questions/311703/algorithm-for-sampling-without-replacement
// Perhaps mines may be generated after first clear to ensure first clear is safe.
// Generate num_mines mines on tiles-1 tiles. If a mine index is greater than or equal to the index of this first click, shift up by 1.

std::vector<std::vector<int>> populate_board(std::vector<std::vector<int>> board, std::set<int> mine_locs, int height, int width)
{
    // std::set<int> mine_locs = rand_combi(tiles, num_mines, engine, distribution);
    for (auto loc : mine_locs) {
        board[loc / width][loc % width] = -1;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (board[i][j] >= 0) {
                for (int vert = -1; vert < 2; vert++) {
                    for (int hor = -1; hor < 2; hor++) {
                        if (vert || hor) {
                            int row = i + vert;
                            int col = j + hor;
                            if (inside_board(row, col, height, width)) {
                                if (board[row][col] == -1) {
                                    board[i][j]++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return board;
}
std::set<int> rand_combi(int n, int k, std::mt19937 &generator, std::uniform_real_distribution<double> distribution)
{
    std::set<int> combi;
    int t = 0;
    int m = 0;
    double u;
    while (m < k) {
        u = distribution(generator);
        if ( (n - t) * u >= k - m ) {
            t++;
        }
        else {
            combi.insert(t);
            t++;
            m++;
        }
    }
    return combi;
}

// Draws current state of board, taking into account which cells have been cleared
void draw_board(std::vector<std::vector<int>> board, std::vector<std::vector<int>> cleared, int height, int width)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (cleared[i][j] == 0) {
                std::cout << "#";
            }
            else if (cleared[i][j] == 1) {
                std::cout << "O";
            }
            else if (cleared[i][j] == 2) {
                if (board[i][j] == -1) std::cout << "X";
                else std::cout << board[i][j];
            }
        }
        std::cout << std::endl;
    }
}

// Determines if a pair of indices corresponds to a position within the game board.
bool inside_board(int row, int col, int height, int width) {
    return row >= 0 && col >= 0 && row < height && col < width;
}
