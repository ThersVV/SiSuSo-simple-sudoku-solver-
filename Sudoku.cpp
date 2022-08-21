#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <tuple>
#include <set>
#include <stack>
#include <map>
#include <algorithm>

using grid = std::vector<std::vector<std::tuple<int, std::set<int>>>>;

std::pair<int, int> findEntryWithLargestValue(std::map<int, int> sampleMap);
void insertSquare(grid &board, const int x, const int y);
void insertLine(grid &board, const int x, const int y);
void insertColumn(grid &board, const int x, const int y);
void printBoard(const grid &board);
void updateBoard(grid &board, const std::set<int> numRange);
grid createBoard();
bool boardDone(const grid &board);
bool boardIsCorrupt(const grid &board);
std::tuple<int, int> findZero(const grid &board);

int main()
{
    std::cout << "Sudoku" << std::endl;
    std::set<int> numRangeInit;
    for (int i = 1; i < 10; ++i)
    {
        numRangeInit.insert(i);
    }
    const std::set<int> numRange = numRangeInit;
    auto board = createBoard();
    auto lastBoard = board;
    std::stack<grid> depthSearchStack{};
    depthSearchStack.push(board);
    while (true)
    {
        if (depthSearchStack.size() == 0)
        {
            std::cout << "shouldn't happen" << std::endl;
            break;
        }
        else
        {
            board = depthSearchStack.top();
            lastBoard = board;
            updateBoard(board, numRange);
            if (boardDone(board))
            {
                printBoard(board);
                break;
            }
            else if (boardIsCorrupt(board))
            {
                depthSearchStack.pop();
            }
            else if (lastBoard == board)
            {
                depthSearchStack.pop();
                auto [y, x] = findZero(board);

                std::set<int> possNums;
                std::set_difference(numRange.begin(), numRange.end(), std::get<1>(board[y][x]).begin(), std::get<1>(board[y][x]).end(),
                                    std::inserter(possNums, possNums.end()));
                for (auto possNum : possNums)
                {
                    std::get<0>(board[y][x]) = possNum;
                    depthSearchStack.push(board);
                }
            }
            else
            {
                depthSearchStack.top() = board;
            }
        }
    }

    return 0;
}
std::tuple<int, int> findZero(const grid &board)
{
    for (int y = 0; y < board.size(); y++)
    {
        for (int x = 0; x < board.size(); x++)
        {
            if (std::get<0>(board[y][x]) == 0)
            {
                return std::make_tuple(y, x);
            }
        }
    }
}
bool boardIsCorrupt(const grid &board)
{
    for (auto a : board)
    {
        for (auto b : a)
        {
            if (std::get<1>(b).size() == 9)
            {
                return true;
            }
        }
    }
    return false;
}
bool boardDone(const grid &board)
{
    for (auto a : board)
    {
        for (auto b : a)
        {
            if (std::get<0>(b) == 0)
            {
                return false;
            }
        }
    }
    return true;
}
grid createBoard()
{
    std::ifstream vstup("zadani.txt");
    grid board;
    for (int i = 0; i < 9; i++)
    {
        std::string levell{};
        std::set<int> emptyy{};
        std::vector<std::tuple<int, std::set<int>>> level{};
        vstup >> levell;
        for (auto &c : levell)
        {
            level.push_back(std::make_tuple(c - '0', emptyy));
        }
        board.push_back(level);
    }
    return board;
}
void printBoard(const grid &board)
{
    std::ofstream vystup("vystup.txt");
    for (auto vec : board)
    {
        int i = 0;
        static int j = 0;
        for (auto tup : vec)
        {
            if (i == 3)
            {

                std::cout << "| ";
                vystup << "| ";
                i = 0;
            }
            std::cout << std::get<0>(tup) << " ";
            vystup << std::get<0>(tup) << " ";
            i++;
        }
        j++;
        if (j % 3 == 0 && j != 9)
        {

            std::cout << "\n______________________\n";
            vystup << "\n______________________\n";
        }
        std::cout << "\n";
        vystup << "\n";
    }
}
void updateBoard(grid &board, const std::set<int> numRange)
{
    for (int y = 0; y < board.size(); y++)
    {
        for (int x = 0; x < board[y].size(); x++)
        {
            int num{std::get<0>(board[y][x])};
            if (num == 0)
            {
                insertLine(board, x, y);
                insertColumn(board, x, y);
                insertSquare(board, x, y);

                if (std::get<1>(board[y][x]).find(0) != std::get<1>(board[y][x]).end())
                {
                    std::get<1>(board[y][x]).erase(std::get<1>(board[y][x]).find(0));
                }
                if (std::get<1>(board[y][x]).size() == 8)
                {
                    std::set<int> possNums;
                    std::set_difference(numRange.begin(), numRange.end(), std::get<1>(board[y][x]).begin(), std::get<1>(board[y][x]).end(),
                                        std::inserter(possNums, possNums.end()));
                    std::get<0>(board[y][x]) = *possNums.begin();
                }
            }
        }
    }
}
void insertSquare(grid &board, const int x, const int y)
{
    std::set<int> *square = &std::get<1>(board[y][x]);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            (*square).insert(std::get<0>(board[(y / 3) * 3 + i][(x / 3) * 3 + j]));
        }
    }
}
void insertLine(grid &board, const int x, const int y)
{
    std::set<int> *square = &std::get<1>(board[y][x]);
    for (auto const &lineSquare : board[y])
    {
        (*square).insert(std::get<0>(lineSquare));
    }
}
void insertColumn(grid &board, const int x, const int y)
{
    std::set<int> *square = &std::get<1>(board[y][x]);
    for (auto &columnSquare : board)
    {
        (*square).insert(std::get<0>(columnSquare[x]));
    }
}