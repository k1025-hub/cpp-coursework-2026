#define main b2_public_main
#include "../src/main/A1_b2.cpp"
#undef main

int main() {
    // 第 1 组：空指针零长度、反向区间且禁止改动原数组。
    CHECK(compact(nullptr, 0, 0, 1) == 0);
    int reversed[]{1, 2};
    CHECK(compact(reversed, 2, 5, 3) == 0);
    CHECK(reversed[0] == 1 && reversed[1] == 2);

    // 第 2 组：闭区间、重复值和稳定顺序，尾部不属于结果。
    int mixed[]{3, 1, 3, 2, 3};
    const std::size_t count = compact(mixed, 5, 2, 3);
    CHECK(count == 4);
    CHECK(mixed[0] == 3 && mixed[1] == 3 && mixed[2] == 2 && mixed[3] == 3);

    // 第 3 组：low=high、全保留、全删除和 int 端点。
    int equal[]{1, 1, 1};
    CHECK(compact(equal, 3, 1, 1) == 3);
    CHECK(equal[0] == 1 && equal[1] == 1 && equal[2] == 1);
    int removed[]{-2, 0, 2};
    CHECK(compact(removed, 3, 3, 4) == 0);
    int extremes[]{std::numeric_limits<int>::max(), 0, std::numeric_limits<int>::min()};
    CHECK(compact(extremes, 3, std::numeric_limits<int>::min(),
                  std::numeric_limits<int>::max()) == 3);
    CHECK(extremes[0] == std::numeric_limits<int>::max() && extremes[1] == 0
          && extremes[2] == std::numeric_limits<int>::min());
    std::cout << "B2 boundary checks passed (3 groups, 10 checks)\n";
}
