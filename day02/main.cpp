#include <iostream>
#include <vector>
#include <cassert>

std::vector<std::pair<int32_t, int32_t>> parseInput() {
    std::vector<std::pair<int32_t, int32_t>> moves;

    std::string direction;
    int32_t distance;
    while (std::cin >> direction) {
        std::cin >> distance;
        std::pair<int32_t, int32_t> p;
        if (direction == "forward")
            p = std::make_pair(distance, 0);
        else {
            if (direction == "up")
                distance = -distance;
            p = std::make_pair(0, distance);
        }
        moves.push_back(p);
    }

    return moves;
}

std::pair<int32_t, int32_t> finalPositionSimple(std::vector<std::pair<int32_t, int32_t>> &moves) {
    std::pair<int32_t, int32_t> position;

    for (const auto &move: moves) {
        position.first += move.first;
        position.second += move.second;
    }

    return position;
}

std::pair<int32_t, int32_t> finalPositionAim(std::vector<std::pair<int32_t, int32_t>> &moves) {
    std::pair<int32_t, int32_t> position;
    int32_t aim = 0;

    for (const auto &move: moves) {
        if (move.first == 0) {
            aim += move.second;
        } else {
            position.first += move.first;
            position.second += aim * move.first;
        }
    }

    return position;
}


int main() {
    auto input = parseInput();

    auto finalPosOne = finalPositionSimple(input);
    int32_t resultOne = finalPosOne.first * finalPosOne.second;
    assert(resultOne == 1694130);
    std::cout << resultOne << std::endl;

    auto finalPosTwo = finalPositionAim(input);
    int32_t resultTwo = finalPosTwo.first * finalPosTwo.second;
    assert(resultTwo == 1698850445);
    std::cout << resultTwo << std::endl;
}
