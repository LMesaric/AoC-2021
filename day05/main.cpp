#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Line {
public:
    const std::pair<uint16_t, uint16_t> start;
    const std::pair<uint16_t, uint16_t> end;

    Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) : start(x1, y1), end(x2, y2) {}
};

std::vector<Line> parseInput() {
    std::vector<Line> lines;

    uint16_t x1, y1, x2, y2;
    for (char ignore; std::cin >> x1;) {
        std::cin >> ignore >> y1;
        std::cin.ignore(4);
        std::cin >> x2 >> ignore >> y2;
        lines.emplace_back(x1, y1, x2, y2);
    }

    return lines;
}

std::pair<uint16_t, uint16_t> dimensions(std::vector<Line> &lines) {
    uint16_t maxX = 0, maxY = 0;
    for (const Line &line: lines) {
        maxX = std::max(maxX, line.start.first);
        maxX = std::max(maxX, line.end.first);
        maxY = std::max(maxY, line.start.second);
        maxY = std::max(maxY, line.end.second);
    }
    return {maxX + 1, maxY + 1};
}

uint32_t calculateTask(std::vector<Line> &lines, bool ignoreDiagonal) {
    auto dim = dimensions(lines);
    std::vector<std::vector<uint8_t>> data;
    data.resize(dim.first, std::vector<uint8_t>(dim.second));

    for (const Line &line: lines) {
        int16_t dx = (int16_t) std::clamp(line.end.first - line.start.first, -1, 1);
        int16_t dy = (int16_t) std::clamp(line.end.second - line.start.second, -1, 1);

        if (ignoreDiagonal && dx && dy)
            continue;

        for (auto[x, y] = line.start;; x += dx, y += dy) {
            if (data[x][y] < 2)
                data[x][y]++;
            if (x == line.end.first && y == line.end.second)
                break;
        }
    }

    uint32_t res = 0;
    for (const auto &row: data)
        for (const uint8_t v: row)
            if (v >= 2)
                res++;

    return res;
}

int main() {
    auto lines = parseInput();

    auto resultOne = calculateTask(lines, true);
    assert(resultOne == 6225);
    std::cout << resultOne << std::endl;

    auto resultTwo = calculateTask(lines, false);
    assert(resultTwo == 22116);
    std::cout << resultTwo << std::endl;
}
