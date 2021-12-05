#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

auto parseInput() {
    std::vector<uint32_t> values;
    std::string value;
    while (std::cin >> value)
        values.push_back(std::stoi(value, nullptr, 2));
    return std::make_pair(values, value.size());
}

uint32_t evaluateCounterMostCommon(std::vector<uint32_t> &counts, uint32_t total) {
    uint32_t val = 0;
    for (const auto count: counts)
        val = (val << 1) + (count * 2 > total);
    return val;
}

inline uint32_t countSetBits(std::vector<uint32_t> &values, uint32_t pos) {
    uint32_t cnt = 0;
    for (const auto v: values)
        cnt += (v >> pos) & 1;
    return cnt;
}

uint32_t calculateFirstTask(std::vector<uint32_t> &values, uint32_t size) {
    std::vector<uint32_t> counts(size);

    for (auto i = size - 1; i < size; --i)
        counts.push_back(countSetBits(values, i));

    auto gamma = evaluateCounterMostCommon(counts, values.size());
    auto epsilon = ~gamma & ((1 << size) - 1);
    return gamma * epsilon;
}

uint32_t genericRating(std::vector<uint32_t> values, uint32_t size, bool flip) {
    for (auto i = size - 1; i < size && values.size() > 1; --i) {
        auto onesCnt = countSetBits(values, i);
        auto picked = flip ^ (onesCnt * 2 >= values.size());

        std::vector<uint32_t> values_tmp;
        std::copy_if(values.begin(), values.end(), std::back_inserter(values_tmp),
                     [=](uint32_t item) { return ((item >> i) & 1) == picked; });
        values = std::move(values_tmp);
    }

    return values[0];
}

uint32_t calculateSecondTask(std::vector<uint32_t> &values, uint32_t size) {
    auto oxygenRating = genericRating(values, size, false);
    auto co2Rating = genericRating(values, size, true);
    return oxygenRating * co2Rating;
}

int main() {
    auto[values, size] = parseInput();

    auto resultOne = calculateFirstTask(values, size);
    assert(resultOne == 1092896);
    std::cout << resultOne << std::endl;

    auto resultTwo = calculateSecondTask(values, size);
    assert(resultTwo == 4672151);
    std::cout << resultTwo << std::endl;
}
