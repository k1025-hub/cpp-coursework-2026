#define main q6_public_main
#include "../src/main/A1_q6.cpp"
#undef main

int main() {
    // 第 1 组：无候选、负射程、零射程，以及三类筛选。
    CHECK(select_target({}, 5) == -1);
    CHECK(select_target({{42, 0, 0, 1, true}}, -1) == -1);
    CHECK(select_target({{1, 0, 0, 1, false}, {2, 0, 0, 0, true},
                         {3, 0, 0, -1, true}, {4, 1, 0, 1, true}}, 0) == -1);
    CHECK(select_target({{42, 0, 0, 1, true}}, 0) == 42);

    // 第 2 组：三个优先级；反转输入不能改变最终选择。
    CHECK(select_target({{7, 3, 4, 1, true}, {2, 0, 0, 2, true}}, 5) == 7);
    CHECK(select_target({{7, 3, 4, 1, true}, {9, 0, 2, 1, true}}, 5) == 9);
    std::vector<Target> tied{{7, 3, 4, 1, true}, {2, 0, 5, 1, true}};
    CHECK(select_target(tied, 5) == 2);
    CHECK(tied[0].id == 7 && tied[1].id == 2);
    std::reverse(tied.begin(), tied.end());
    CHECK(select_target(tied, 5) == 2);

    // 第 3 组：百万级坐标、负坐标和射程内外边界，防止 int 平方溢出。
    CHECK(select_target({{8, -1000000, 0, 3, true},
                         {1, 1000000, 1, 1, true}}, 1000000) == 8);
    CHECK(select_target({{1, 1000000, 1000000, 1, true}}, 1000000) == -1);
    std::cout << "Q6 boundary checks passed (3 groups, 11 checks)\n";
}
