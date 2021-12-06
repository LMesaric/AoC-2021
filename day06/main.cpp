#include <array>
#include <cassert>
#include <iostream>
#include <string>

#define M 6
#define N 9

std::array<uint64_t, N> parseInput() {
    std::string line;
    std::getline(std::cin, line);
    std::array<uint64_t, N> state{};

    for (int i = 0; i < line.size(); i += 2)
        state[line[i] - '0']++;  // avoid parsing integers

    return state;
}

void iter(std::array<uint64_t, N> &state) {
    auto numZeros = state[0];
    for (int i = 1; i < N; ++i)
        state[i - 1] = state[i];
    state[N - 1] = numZeros;
    state[M] += numZeros;
}

uint64_t calculateTask(std::array<uint64_t, N> &state, int iterations) {
    for (int i = 0; i < iterations; ++i)
        iter(state);

    uint64_t sum = 0;
    for (const auto v: state)
        sum += v;
    return sum;
}

int main() {
    auto state = parseInput();

    auto resultOne = calculateTask(state, 80);
    assert(resultOne == 360761);
    std::cout << resultOne << std::endl;

    auto resultTwo = calculateTask(state, 256 - 80);
    assert(resultTwo == 1632779838045);
    std::cout << resultTwo << std::endl;
}
