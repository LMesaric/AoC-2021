#include <iostream>
#include <vector>
#include <cassert>

std::vector<int32_t> parseInput() {
    std::vector<int32_t> depths;
    int32_t depth;
    while (std::cin >> depth) {
        depths.push_back(depth);
    }
    return depths;
}

int32_t countIncreasing(std::vector<int32_t> &depths, uint32_t dist) {
    int32_t cnt = 0;
    for (auto i = dist; i < depths.size(); ++i)
        cnt += depths[i] > depths[i - dist];
    return cnt;
}

int32_t countIncreasingSingle(std::vector<int32_t> &depths) {
    return countIncreasing(depths, 1);
}

int32_t countIncreasingSliding(std::vector<int32_t> &depths) {
    return countIncreasing(depths, 3);
}

int main() {
    std::vector<int32_t> input = parseInput();

    int32_t countOne = countIncreasingSingle(input);
    assert(countOne == 1316);
    std::cout << countOne << std::endl;

    int32_t countTwo = countIncreasingSliding(input);
    assert(countTwo == 1344);
    std::cout << countTwo << std::endl;
}
