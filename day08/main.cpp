#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define N 10
#define M 4

struct Task {
    std::string inputs[N];  // sizes in order: 2 3 4 5 5 5 6 6 6 7
    std::string outputs[M];
};

std::vector<Task> parseInput() {
    std::vector<Task> tasks;
    std::string line;

    while (std::getline(std::cin, line)) {
        tasks.emplace_back();
        Task &task = tasks.back();
        std::stringstream ss(line);
        for (auto &input: task.inputs) {
            ss >> input;
            std::sort(input.begin(), input.end());
        }
        std::sort(task.inputs, task.inputs + N,
                  [](const std::string &s1, const std::string &s2) { return s1.size() < s2.size(); });

        ss.ignore(3);
        for (auto &output: task.outputs) {
            ss >> output;
            std::sort(output.begin(), output.end());
        }
    }

    return tasks;
}

template<auto... ts, typename T>
constexpr auto isInList(const T &t) {
    return ((t == ts) || ...);
}

int32_t calculateFirstTask(const std::vector<Task> &tasks) {
    int32_t sum = 0;
    for (const auto &task: tasks)
        for (const auto &output: task.outputs)
            sum += isInList<2, 3, 4, 7>(output.size());
    return sum;
}

bool isCharInString(const char c, const std::string &s) {
    return std::ranges::any_of(s.cbegin(), s.cend(), [=](const char i) { return c == i; });
}

bool isContained(const std::string &smaller, const std::string &larger) {
    return std::ranges::all_of(smaller.cbegin(), smaller.cend(),
                               [&](const char c) { return isCharInString(c, larger); });
}

int findThree(const Task &task, const int sevenPos) {
    for (int i = 3; i <= 5; ++i)  // numbers 2, 3, 5 (size 5)
        if (isContained(task.inputs[sevenPos], task.inputs[i]))
            return i;
    return -1;  // will not happen
}

int findFive(const Task &task, const int sixPos) {
    for (int i = 3; i <= 5; ++i)  // numbers 2, 3, 5 (size 5)
        if (isContained(task.inputs[i], task.inputs[sixPos]))
            return i;
    return -1;  // will not happen
}

int findSix(const Task &task, const int onePos) {
    for (int i = 6; i <= 8; ++i)  // numbers 0, 6, 9 (size 6)
        if (!isContained(task.inputs[onePos], task.inputs[i]))
            return i;
    return -1;  // will not happen
}

int findNine(const Task &task, const int fourPos) {
    for (int i = 6; i <= 8; ++i)  // numbers 0, 6, 9 (size 6)
        if (isContained(task.inputs[fourPos], task.inputs[i]))
            return i;
    return -1;  // will not happen
}

int32_t parseNumber(const Task &task, const int decoded[N]) {
    int32_t num = 0;
    for (const auto &str: task.outputs)
        for (int i = 0; i < N; ++i)
            if (task.inputs[decoded[i]] == str) {
                num = num * 10 + i;
                break;
            }
    return num;
}

void decodeTask(const Task &task, int decoded[N]) {
    decoded[1] = 0;  // size 2
    decoded[7] = 1;  // size 3
    decoded[4] = 2;  // size 4
    decoded[8] = 9;  // size 7

    decoded[3] = findThree(task, decoded[7]);
    decoded[6] = findSix(task, decoded[1]);
    decoded[5] = findFive(task, decoded[6]);
    decoded[9] = findNine(task, decoded[4]);

    decoded[0] = 21 - decoded[6] - decoded[9];
    decoded[2] = 12 - decoded[3] - decoded[5];
}

int32_t calculateSecondTask(const std::vector<Task> &tasks) {
    int32_t sum = 0;
    for (const auto &task: tasks) {
        int decoded[N];
        decodeTask(task, decoded);
        sum += parseNumber(task, decoded);
    }
    return sum;
}

int main() {
    auto tasks = parseInput();

    auto resultOne = calculateFirstTask(tasks);
    assert(resultOne == 344);
    std::cout << resultOne << std::endl;

    auto resultTwo = calculateSecondTask(tasks);
    assert(resultTwo == 1048410);
    std::cout << resultTwo << std::endl;
}
