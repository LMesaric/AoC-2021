#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

std::vector<int32_t> parseInput() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::vector<int32_t> positions;

    for (int32_t i; ss >> i;) {
        positions.push_back(i);
        if (ss.peek() != ',')
            break;
        ss.ignore();
    }

    return positions;
}

int32_t findMedian(std::vector<int32_t> &values) {
    std::sort(values.begin(), values.end());
    return values[values.size() / 2];
}

int32_t sumDistancesLinear(std::vector<int32_t> &values, int32_t p) {
    int32_t sum = 0;
    for (const auto v: values)
        sum += abs(p - v);
    return sum;
}

int64_t sumDistancesQuadratic(std::vector<int32_t> &values, int32_t p) {
    int64_t sum = 0;
    for (const auto v: values) {
        const auto dist = abs(p - v);
        sum += dist * (dist + 1);
    }
    return sum / 2;
}

int32_t calculateFirstTask(std::vector<int32_t> &positions) {
    const auto median = findMedian(positions);
    return sumDistancesLinear(positions, median);
}

int64_t calculateSecondTask(std::vector<int32_t> &positions) {
    const double sum = std::accumulate(positions.begin(), positions.end(), 0);
    const double avg = sum / positions.size();
    return std::min(
            sumDistancesQuadratic(positions, floor(avg)),
            sumDistancesQuadratic(positions, ceil(avg))
    );
}

int main() {
    auto positions = parseInput();

    auto resultOne = calculateFirstTask(positions);
    assert(resultOne == 355150);
    std::cout << resultOne << std::endl;

    auto resultTwo = calculateSecondTask(positions);
    assert(resultTwo == 98368490);
    std::cout << resultTwo << std::endl;
}
