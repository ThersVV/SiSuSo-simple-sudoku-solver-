#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>
#include <set>
#include <map>
#include <algorithm>

std::pair<int, int> findEntryWithLargestValue(std::map<int, int> sampleMap);

int main()
{
    std::ifstream vstup("zadani.txt");
    std::ofstream vystup("vystup.txt");
    std::cout << "Sudoku" << std::endl;
    std::vector<std::vector<std::tuple<int, std::set<int>>>> board;
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
    while (true)
    {
        auto lastBoard = board;
        for (int y = 0; y < board.size(); y++)
        {
            for (int x = 0; x < board[y].size(); x++)
            {
                int num{std::get<0>(board[y][x])};
                if (num == 0)
                {
                    for (auto &neco : board[y])
                    {
                        std::get<1>(board[y][x]).insert(std::get<0>(neco));
                    }
                    for (auto &neco : board)
                    {
                        std::get<1>(board[y][x]).insert(std::get<0>(neco[x]));
                    }
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3][(x / 3) * 3]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 1][(x / 3) * 3]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 2][(x / 3) * 3]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3][(x / 3) * 3 + 1]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 1][(x / 3) * 3 + 1]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 2][(x / 3) * 3 + 1]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3][(x / 3) * 3 + 2]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 1][(x / 3) * 3 + 2]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 2][(x / 3) * 3 + 2]));

                    if (std::get<1>(board[y][x]).find(0) != std::get<1>(board[y][x]).end())
                    {
                        std::get<1>(board[y][x]).erase(std::get<1>(board[y][x]).find(0));
                    }
                    if (std::get<1>(board[y][x]).size() == 8)
                    {
                        if (std::get<1>(board[y][x]).find(1) == std::get<1>(board[y][x]).end())
                        {
                            std::get<0>(board[y][x]) = 1;
                        }
                        else if (std::get<1>(board[y][x]).find(2) == std::get<1>(board[y][x]).end())
                        {
                            std::get<0>(board[y][x]) = 2;
                        }
                        else if (std::get<1>(board[y][x]).find(3) == std::get<1>(board[y][x]).end())
                        {

                            std::get<0>(board[y][x]) = 3;
                        }
                        else if (std::get<1>(board[y][x]).find(4) == std::get<1>(board[y][x]).end())
                        {

                            std::get<0>(board[y][x]) = 4;
                        }
                        else if (std::get<1>(board[y][x]).find(5) == std::get<1>(board[y][x]).end())
                        {

                            std::get<0>(board[y][x]) = 5;
                        }
                        else if (std::get<1>(board[y][x]).find(6) == std::get<1>(board[y][x]).end())
                        {

                            std::get<0>(board[y][x]) = 6;
                        }
                        else if (std::get<1>(board[y][x]).find(7) == std::get<1>(board[y][x]).end())
                        {

                            std::get<0>(board[y][x]) = 7;
                        }
                        else if (std::get<1>(board[y][x]).find(8) == std::get<1>(board[y][x]).end())
                        {

                            std::get<0>(board[y][x]) = 8;
                        }
                        else
                        {
                            std::get<0>(board[y][x]) = 9;
                        }
                    }
                }
            }
        }
        for (int y = 0; y < board.size(); y++)
        {
            for (int x = 0; x < board[y].size(); x++)
            {
                int num{std::get<0>(board[y][x])};
                if (num == 0)
                {

                    for (auto &neco : board[y])
                    {
                        std::get<1>(board[y][x]).insert(std::get<0>(neco));
                    }
                    for (auto &neco : board)
                    {
                        std::get<1>(board[y][x]).insert(std::get<0>(neco[x]));
                    }
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3][(x / 3) * 3]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 1][(x / 3) * 3]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 2][(x / 3) * 3]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3][(x / 3) * 3 + 1]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 1][(x / 3) * 3 + 1]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 2][(x / 3) * 3 + 1]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3][(x / 3) * 3 + 2]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 1][(x / 3) * 3 + 2]));
                    std::get<1>(board[y][x]).insert(std::get<0>(board[(y / 3) * 3 + 2][(x / 3) * 3 + 2]));

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
        }
        if (lastBoard == board)
        {
            break;
        }
    }

    for (auto vec : board)
    {
        for (auto tup : vec)
        {
            std::cout << std::get<0>(tup) << " ";
            vystup << std::get<0>(tup) << " ";
        }
        std::cout << "\n";
        vystup << "\n";
    }
    return 0;
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