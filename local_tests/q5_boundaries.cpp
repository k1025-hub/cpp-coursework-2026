#define main q5_public_main
#include "../src/main/A1_q5.cpp"
#undef main

int main() {
    // 第 1 组：空地图合法，但零列、不等长、最后一格非法必须抛异常。
    CHECK(risk({}).empty());
    EXPECT_INVALID(risk({""}));
    EXPECT_INVALID(risk({"..", "."}));
    EXPECT_INVALID(risk({"..", ".x"}));

    // 第 2 组：单格、单行、单列；地图外部不算障碍。
    CHECK(risk({"."}) == std::vector<std::vector<int>>({{0}}));
    CHECK(risk({"#.#"}) == std::vector<std::vector<int>>({{-1, 2, -1}}));
    CHECK(risk({".", "#"}) == std::vector<std::vector<int>>({{1}, {-1}}));

    // 第 3 组：只计四邻域、四面包围、全障碍，并核对输入不变。
    const std::vector<std::string> grid{"#.", ".."};
    const auto original = grid;
    CHECK(risk(grid) == std::vector<std::vector<int>>({{-1, 1}, {1, 0}}));
    CHECK(grid == original);
    CHECK(risk({".#.", "#.#", ".#."})
          == std::vector<std::vector<int>>({{2, -1, 2}, {-1, 4, -1}, {2, -1, 2}}));
    CHECK(risk({"##", "##"}) == std::vector<std::vector<int>>({{-1, -1}, {-1, -1}}));
    std::cout << "Q5 boundary checks passed (3 groups, 11 checks)\n";
}
