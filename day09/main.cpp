#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::vector<uint8_t>> parseInput() {
    std::vector<std::vector<uint8_t>> grid;
    std::string line;

    while (std::getline(std::cin, line)) {
        grid.emplace_back();
        std::vector<uint8_t> &row = grid.back();
        std::stringstream ss(line);
        for (uint8_t c; ss >> c;)
            grid.back().push_back(c - '0');
    }

    return grid;
}

std::vector<std::pair<int, int>> findLowPositions(const std::vector<std::vector<uint8_t>> &grid) {
    const auto rowNum = grid.size();
    const auto colNum = grid[0].size();

    std::vector<std::pair<int, int>> positions;
    for (int row = 0; row < rowNum; ++row) {
        for (int col = 0; col < colNum; ++col) {
            auto const currentVal = grid[row][col];
            if (row > 0 && grid[row - 1][col] <= currentVal)
                continue;
            if (row < rowNum - 1 && grid[row + 1][col] <= currentVal)
                continue;
            if (col > 0 && grid[row][col - 1] <= currentVal)
                continue;
            if (col < colNum - 1 && grid[row][col + 1] <= currentVal)
                continue;

            positions.emplace_back(row, col);
        }
    }

    return positions;
}

int32_t calculateFirstTask(const std::vector<std::vector<uint8_t>> &grid,
                           const std::vector<std::pair<int, int>> &lows) {
    int32_t sum = 0;
    for (const auto &p: lows)
        sum += grid[p.first][p.second] + 1;
    return sum;
}

int32_t bfs(const std::vector<std::vector<uint8_t>> &grid,
            std::vector<std::vector<uint8_t>> &visited,
            const std::pair<int, int> &start) {

    if (visited[start.first][start.second])
        return -1;  // should never happen for good input

    const auto rowNum = grid.size();
    const auto colNum = grid[0].size();

    int32_t basinSize = 0;
    std::deque<std::pair<int, int>> toVisit = {start};
    while (!toVisit.empty()) {
        auto[currentRow, currentCol] = toVisit.front();
        toVisit.pop_front();
        if (visited[currentRow][currentCol] || grid[currentRow][currentCol] >= 9)
            continue;

        visited[currentRow][currentCol] = true;
        basinSize++;
        if (currentRow > 0)
            toVisit.emplace_back(currentRow - 1, currentCol);
        if (currentRow < rowNum - 1)
            toVisit.emplace_back(currentRow + 1, currentCol);
        if (currentCol > 0)
            toVisit.emplace_back(currentRow, currentCol - 1);
        if (currentCol < colNum - 1)
            toVisit.emplace_back(currentRow, currentCol + 1);
    }

    return basinSize;
}

int32_t calculateSecondTask(const std::vector<std::vector<uint8_t>> &grid,
                            const std::vector<std::pair<int, int>> &lows) {

    std::vector<std::vector<uint8_t>> visited;
    visited.resize(grid.size(), std::vector<uint8_t>(grid[0].size(), false));

    std::vector<int32_t> basinSizes;
    for (const auto &p: lows) {
        auto basinSize = bfs(grid, visited, p);
        if (basinSize > 0)
            basinSizes.push_back(basinSize);
    }

    std::sort(basinSizes.rbegin(), basinSizes.rend());
    return basinSizes[0] * basinSizes[1] * basinSizes[2];
}

int main() {
    const auto grid = parseInput();

    const auto lows = findLowPositions(grid);

    auto resultOne = calculateFirstTask(grid, lows);
    assert(resultOne == 588);
    std::cout << resultOne << std::endl;

    auto resultTwo = calculateSecondTask(grid, lows);
    assert(resultTwo == 964712);
    std::cout << resultTwo << std::endl;
}
