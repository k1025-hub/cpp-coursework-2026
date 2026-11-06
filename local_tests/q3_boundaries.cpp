#define main q3_public_main
#include "../src/main/A1_q3.cpp"
#undef main

int main() {
    // 第 1 组：空输入与无效窗口，不生成不完整窗口。
    CHECK(alarms({}, 1, 0).empty());
    CHECK(alarms({1, 2}, 0, 0).empty());
    CHECK(alarms({1, 2}, -1, 0).empty());
    CHECK(alarms({1, 2}, 3, 0).empty());

    // 第 2 组：负数、严格大于，以及 k=1、k=n。
    CHECK(alarms({-4, -3, -2}, 2, -6) == std::vector<int>({2}));
    CHECK(alarms({-2, -1, 0}, 1, -1) == std::vector<int>({2}));
    CHECK(alarms({-2, -1, 0}, 3, -3).empty());
    CHECK(alarms({-2, -1, 0}, 3, -4) == std::vector<int>({2}));

    // 第 3 组：最大规模，窗口和超出 32 位整数范围。
    const std::vector<int> large(200000, 1000000000);
    CHECK(alarms(large, 200000, 199999999999999LL)
          == std::vector<int>({199999}));
    CHECK(alarms(large, 200000, 200000000000000LL).empty());
    std::cout << "Q3 boundary checks passed (3 groups, 10 checks)\n";
}
