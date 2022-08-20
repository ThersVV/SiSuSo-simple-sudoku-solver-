#include <string>
#include <fstream>
#include <vector>
#include <iostream>
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
bool boardDone(grid board);
bool boardIsCorrupt(grid board);
const std::tuple<int, std::set<int>> *findZero(const grid &board);

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
    std::stack<grid> stanck{};
    stanck.push(board);
    int counter0{0};
    int counter1{0};
    int counter2{0};
    int counter3{0};
    int counter4{0};
    while (true)
    {
        counter0++;
        if (stanck.size() == 0)
        {
            std::cout << "shouldn't happen" << std::endl;
            break;
        }
        else
        {
            board = stanck.top();
            lastBoard = board;
            updateBoard(board, numRange);
            if (boardDone(board))
            {
                printBoard(board);
                break;
            }
            else if (boardIsCorrupt(board))
            {
                stanck.pop();
            }
            else if (lastBoard == board)
            {

                bool exit{false};
                for (int y = 0; y < board.size(); y++)
                {
                    for (int x = 0; x < board.size(); x++)
                    {
                        const auto b = board[y][x];
                        if (std::get<0>(b) == 0)
                        {
                            stanck.pop();

                            std::set<int> result;
                            std::set_difference(numRange.begin(), numRange.end(), std::get<1>(board[y][x]).begin(), std::get<1>(board[y][x]).end(),
                                                std::inserter(result, result.end()));
                            for (auto p : result)
                            {
                                auto boardCopy = board;
                                std::get<0>(boardCopy[y][x]) = p;
                                stanck.push(boardCopy);
                            }
                            exit = true;
                        }
                        if (exit)
                        {
                            break;
                        }
                    }
                    if (exit)
                    {
                        break;
                    }
                }
            }
            else
            {
                stanck.top() = board;
            }
        }
    }

    return 0;
}
/* const std::tuple<int, std::set<int>> *findZero(const grid &board)
{
    for (const auto &a : board)
    {
        for (const auto &b : a)
        {
            if (std::get<0>(b) == 0)
            {
                return &b;
            }
        }
    }
} */
bool boardIsCorrupt(grid board)
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
bool boardDone(grid board)
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

            std::cout << "\n_______________________\n";
            vystup << "\n_______________________\n";
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
                    std::set<int> result;
                    std::set_difference(numRange.begin(), numRange.end(), std::get<1>(board[y][x]).begin(), std::get<1>(board[y][x]).end(),
                                        std::inserter(result, result.end()));
                    std::get<0>(board[y][x]) = *result.begin();
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
std::pair<int, int> findEntryWithLargestValue(
    std::map<int, int> sampleMap)
{
    // Reference variable to help find
    // the entry with the highest value
    std::pair<int, int> entryWithMaxValue = std::make_pair(0, 0);

    // Iterate in the map to find the required entry
    std::map<int, int>::iterator currentEntry;
    for (currentEntry = sampleMap.begin();
         currentEntry != sampleMap.end();
         ++currentEntry)
    {

        // If this entry's value is more
        // than the max value
        // Set this entry as the max
        if (currentEntry->second > entryWithMaxValue.second)
        {

            entryWithMaxValue = std::make_pair(
                currentEntry->first,
                currentEntry->second);
        }
    }

    return entryWithMaxValue;
}

/*
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

                     std::vector<int> allNums;
                     int zeroCounter{0};
                     allNums.reserve(100);
                     for (int count = 0; count < board[y].size(); count++)
                     {
                         auto neco = board[y][count];
                         if (count != x && std::get<0>(neco) == 0)
                         {
                             ++zeroCounter;
                             allNums.insert(allNums.end(), std::get<1>(neco).begin(), std::get<1>(neco).end());
                         }
                     }
                     std::map<int, int> counters;
                     for (auto i : allNums)
                     {
                         if (std::get<1>(board[y][x]).find(i) == std::get<1>(board[y][x]).end())
                         {
                             ++counters[i];
                         }
                     }
                     auto var{*std::max_element(counters.begin(), counters.end())};
                     if (std::get<1>(var) == zeroCounter)
                     {
                         std::get<0>(board[y][x]) = std::get<0>(var);
                     }
                     allNums.clear();
                     zeroCounter = 0;
                     counters.clear();
                     for (int count = 0; count < board.size(); count++)
                     {
                         auto neco = board[count];
                         if (count != y && std::get<0>(neco[x]) == 0)
                         {
                             ++zeroCounter;
                             allNums.insert(allNums.end(), std::get<1>(neco[x]).begin(), std::get<1>(neco[x]).end());
                         }
                     }
                     for (auto i : allNums)
                     {
                         if (std::get<1>(board[y][x]).find(i) == std::get<1>(board[y][x]).end())
                         {
                             ++counters[i];
                         }
                     }
                     auto var2{*std::max_element(counters.begin(), counters.end())};
                     if (std::get<1>(var2) == zeroCounter && std::get<1>(board[y][x]).find(std::get<0>(var2)) == std::get<1>(board[y][x]).end())
                     {
                         std::get<0>(board[y][x]) = std::get<0>(var2);
                     }
                     allNums.clear();
                     zeroCounter = 0;
                     counters.clear();

                     std::vector<std::tuple<int, std::set<int>>> considering{};
                     considering.reserve(9);
                     considering.push_back(board[(y / 3) * 3][(x / 3) * 3]);
                     considering.push_back(board[(y / 3) * 3 + 1][(x / 3) * 3]);
                     considering.push_back(board[(y / 3) * 3 + 2][(x / 3) * 3]);
                     considering.push_back(board[(y / 3) * 3][(x / 3) * 3 + 1]);
                     considering.push_back(board[(y / 3) * 3 + 1][(x / 3) * 3 + 1]);
                     considering.push_back(board[(y / 3) * 3 + 2][(x / 3) * 3 + 1]);
                     considering.push_back(board[(y / 3) * 3][(x / 3) * 3 + 2]);
                     considering.push_back(board[(y / 3) * 3 + 1][(x / 3) * 3 + 2]);
                     considering.push_back(board[(y / 3) * 3 + 2][(x / 3) * 3 + 2]);
                     {
                         auto idk = std::remove(considering.begin(), considering.end(), board[y][x]);
                         considering.erase(idk, considering.end());
                     }
                     while (considering.size() < 8)
                     {
                         considering.push_back(board[y][x]);
                     }
                     for (int count = 0; count < considering.size(); count++)
                     {
                         auto neco = considering[count];
                         if (std::get<0>(neco) == 0)
                         {
                             ++zeroCounter;
                             allNums.insert(allNums.end(), std::get<1>(neco).begin(), std::get<1>(neco).end());
                         }
                     }

                     for (auto i : allNums)
                     {
                         if (std::get<1>(board[y][x]).find(i) == std::get<1>(board[y][x]).end())
                         {
                             ++counters[i];
                         }
                     }
                     auto var3{findEntryWithLargestValue(counters)};
                     if (std::get<1>(var3) == zeroCounter && std::get<1>(board[y][x]).find(std::get<0>(var3)) == std::get<1>(board[y][x]).end())
                     {
                         std::get<0>(board[y][x]) = std::get<0>(var3);
                     }
                 }
             }
         } */