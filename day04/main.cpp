#include <cassert>
#include <iostream>
#include <vector>

#define N 5

class Board {
    uint16_t hitsRows[N]{};
    uint16_t hitsCols[N]{};
    uint32_t sumHitValues = 0;

public:
    uint16_t data[N][N]{};

    bool mark(uint16_t draw) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (data[i][j] == draw) {
                    sumHitValues += draw;
                    return ++hitsRows[i] >= N || ++hitsCols[j] >= N;
                }
            }
        }
        return false;
    }

    uint32_t sumUnmarked() {
        uint32_t boardSum = 0;
        for (auto &row: data)
            for (uint16_t v: row)
                boardSum += v;
        return boardSum - sumHitValues;
    }
};

std::pair<std::vector<uint16_t>, std::vector<Board>> parseInput() {
    std::vector<uint16_t> drawn;
    for (uint16_t i; std::cin >> i;) {
        drawn.push_back(i);
        if (std::cin.peek() == ',')
            std::cin.ignore();
        else
            break;
    }

    std::vector<Board> boards;
    while (std::cin.peek() != EOF) {
        boards.emplace_back();
        for (auto &row: boards.back().data)
            for (uint16_t &j: row)
                std::cin >> j;
        std::cin.ignore();
    }

    return std::make_pair(drawn, boards);
}

std::pair<uint32_t, uint32_t> calculateBothTasks(std::vector<uint16_t> &draws, std::vector<Board> &boards) {
    std::vector<char> wonBoards;
    wonBoards.resize(boards.size());
    uint16_t boardsNotWonCnt = boards.size();

    uint32_t firstScore = 0;

    for (const uint16_t draw: draws) {
        for (int i = 0; i < boards.size(); ++i) {
            if (wonBoards[i])
                continue;

            Board &board = boards[i];
            if (!board.mark(draw))
                continue;

            if (boardsNotWonCnt == boards.size())
                firstScore = (uint32_t) draw * board.sumUnmarked();

            wonBoards[i] = true;
            if (--boardsNotWonCnt <= 0) {
                uint32_t lastScore = (uint32_t) draw * board.sumUnmarked();
                return {firstScore, lastScore};
            }
        }
    }
    return {};
}

int main() {
    auto[draws, boards] = parseInput();

    auto[resultOne, resultTwo] = calculateBothTasks(draws, boards);

    assert(resultOne == 10374);
    assert(resultTwo == 24742);

    std::cout << resultOne << std::endl;
    std::cout << resultTwo << std::endl;
}
