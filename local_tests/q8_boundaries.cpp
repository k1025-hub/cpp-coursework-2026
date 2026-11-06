#define main q8_public_main
#include "../src/main/A1_q8.cpp"
#undef main

int main() {
    // 第 1 组：非法记录不占编号，已见编号的非法记录仍归 invalid。
    const auto validation = summarize({{1, -1001}, {1, 30}, {1, 1001}, {1, 90},
                                       {std::numeric_limits<int>::min(), 1},
                                       {std::numeric_limits<int>::max(), 1}});
    CHECK(validation.valid == 1 && validation.duplicate == 1 && validation.invalid == 4);
    CHECK(validation.total_hp == 30 && validation.ids == std::vector<int>({1}));
    CHECK(validation.valid + validation.duplicate + validation.invalid == 6);
    CHECK(validation.valid == static_cast<int>(validation.ids.size()));

    // 第 2 组：范围端点合法；接收范围与累计范围不同；编号必须升序。
    const std::vector<Telemetry> frames{{9999, 1000}, {0, -1000}, {2, -5}, {1, 200}};
    const auto endpoints = summarize(frames);
    CHECK(endpoints.valid == 4 && endpoints.duplicate == 0 && endpoints.invalid == 0);
    CHECK(endpoints.total_hp == 200 && endpoints.ids == std::vector<int>({0, 1, 2, 9999}));
    CHECK(frames[0].id == 9999 && frames[0].hp == 1000 && frames[1].id == 0);

    // 第 3 组：连续调用独立，空批次完全初始化。
    const auto fresh = summarize({{1, 42}});
    CHECK(fresh.valid == 1 && fresh.duplicate == 0 && fresh.invalid == 0
          && fresh.total_hp == 42 && fresh.ids == std::vector<int>({1}));
    const auto empty = summarize({});
    CHECK(empty.valid == 0 && empty.duplicate == 0 && empty.invalid == 0
          && empty.total_hp == 0 && empty.ids.empty());
    std::cout << "Q8 boundary checks passed (3 groups, 9 checks)\n";
}
