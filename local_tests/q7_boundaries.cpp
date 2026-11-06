#define main q7_public_main
#include "../src/main/A1_q7.cpp"
#undef main

int main() {
    // 第 1 组：空序列不冷却，零请求只冷却，热量最低归零。
    const auto empty = simulate(4, 80, 10, 30, {});
    CHECK(empty.shots == 0 && empty.rejected == 0 && empty.ammo == 4 && empty.heat == 80);
    const auto idle = simulate(4, 5, 10, 30, {0});
    CHECK(idle.shots == 0 && idle.rejected == 0 && idle.ammo == 4 && idle.heat == 0);

    // 第 2 组：无弹也先冷却；零冷却与零射击热量；拒绝不扣弹。
    const auto no_ammo = simulate(0, 50, 10, 20, {1});
    CHECK(no_ammo.shots == 0 && no_ammo.rejected == 1 && no_ammo.ammo == 0 && no_ammo.heat == 40);
    const auto zero_heat = simulate(1, 100, 0, 0, {1});
    CHECK(zero_heat.shots == 1 && zero_heat.rejected == 0 && zero_heat.ammo == 0 && zero_heat.heat == 100);
    const auto too_hot = simulate(1, 100, 0, 1, {1});
    CHECK(too_hot.shots == 0 && too_hot.rejected == 1 && too_hot.ammo == 1 && too_hot.heat == 100);

    // 第 3 组：冷却后恰好到上限可以发射，失败帧也保留冷却效果。
    const std::vector<int> requests{1, 1, 1};
    const auto firing = simulate(2, 90, 10, 20, requests);
    CHECK(firing.shots == 2 && firing.rejected == 1 && firing.ammo == 0 && firing.heat == 100);
    CHECK(firing.shots + firing.rejected == static_cast<int>(requests.size()));
    CHECK(firing.shots + firing.ammo == 2);
    CHECK(requests == std::vector<int>({1, 1, 1}));
    std::cout << "Q7 boundary checks passed (3 groups, 9 checks)\n";
}
