#include <algorithm>
#include <cassert>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

std::vector<std::string> parseInput() {
    std::vector<std::string> brackets;

    for (std::string line; std::getline(std::cin, line);)
        brackets.push_back(line);

    return brackets;
}

template<auto... ts, typename T>
constexpr auto isInList(const T &t) {
    return ((t == ts) || ...);
}

constexpr int32_t remapScore(const char c) {
    switch (c) {
        case ')':
            return 3;
        case ']':
            return 57;
        case '}':
            return 1197;
        case '>':
            return 25137;

        case '(':
            return 1;
        case '[':
            return 2;
        case '{':
            return 3;
        case '<':
            return 4;

        default:
            return 0;
    }
}

constexpr char openingPair(const char c) {
    return (char) (c == ')' ? c - 1 : c - 2);
}

int64_t repairScore(std::vector<char> &stack) {
    int64_t score = 0ll;
    for (const char c: std::ranges::reverse_view(stack))
        score = score * 5 + remapScore(c);
    return score;
}

char minimizeStack(const std::string &line, std::vector<char> &stack) {
    stack.reserve(line.size());

    for (const char c: line) {
        if (isInList<'(', '[', '{', '<'>(c)) {
            stack.push_back(c);
        } else if (stack.empty() || stack.back() != openingPair(c)) {
            return c;
        } else {
            stack.pop_back();
        }
    }

    return 0;
}

std::pair<int32_t, int64_t> calculateBothTasks(const std::vector<std::string> &brackets) {
    int32_t sumCorrupt = 0;
    std::vector<int64_t> resultsRepair;
    std::vector<char> stack;

    for (const auto &line: brackets) {
        char c = minimizeStack(line, stack);
        if (c > 0)
            sumCorrupt += remapScore(c);
        else
            resultsRepair.push_back(repairScore(stack));
        stack.clear();
    }

    std::sort(resultsRepair.begin(), resultsRepair.end());

    return {sumCorrupt, resultsRepair[resultsRepair.size() / 2]};
}

int main() {
    const auto brackets = parseInput();

    const auto[resultOne, resultTwo] = calculateBothTasks(brackets);

    assert(resultOne == 311949);
    assert(resultTwo == 3042730309);

    std::cout << resultOne << std::endl;
    std::cout << resultTwo << std::endl;
}
