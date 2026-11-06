#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q5; see 题面.pdf.
namespace aim::q5 {


// BEGIN IMPLEMENTATION
// aim-cpp-cw
std::vector<std::vector<int>> risk(const std::vector<std::string>& grid) {
    if (grid.empty()) {
        return {};
    }
    const std::size_t columns = grid.front().size();
    if (columns == 0) {
        throw std::invalid_argument("grid must have at least one column");
    }
    // 先验证完整地图，再创建和计算结果。
    for (const std::string& row : grid) {
        if (row.size() != columns) {
            throw std::invalid_argument("grid rows must have equal length");
        }
        for (char cell : row) {
            if (cell != '.' && cell != '#') {
                throw std::invalid_argument("invalid grid character");
            }
        }
    }

    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(columns);
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0));
    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (grid[row][col] == '#') {
                result[row][col] = -1;
                continue;
            }
            for (int direction = 0; direction < 4; ++direction) {
                const int nr = row + dr[direction];
                const int nc = col + dc[direction];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols
                    && grid[nr][nc] == '#') {
                    ++result[row][col];
                }
            }
        }
    }
    return result;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q5;
int main() {
    try {
        { CHECK((risk({".#",".."})==std::vector<std::vector<int>>{{1,-1},{0,1}})); }
        { CHECK(risk({}).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
