// These are local tests; only the original implementation regions are graded.
#define main q3_public_main
#include "../src/main/A1_q3.cpp"
#undef main
#define main q6_public_main
#include "../src/main/A1_q6.cpp"
#undef main
#define main q8_public_main
#include "../src/main/A1_q8.cpp"
#undef main
#define main b2_public_main
#include "../src/main/A1_b2.cpp"
#undef main

int main() {
    // Q3: maximum n, many overlapping windows, negative values and large sums.
    std::vector<int> values(200000);
    for (int i = 0; i < 200000; ++i) {
        values[i] = i % 2 == 0 ? 1000000000 : -1000000000;
    }
    CHECK(aim::q3::alarms(values, 199999, 0) == std::vector<int>({199998}));
    CHECK(aim::q3::alarms(values, 200000, 0).empty());
    const auto singletons = aim::q3::alarms(values, 1, 0);
    CHECK(singletons.size() == 100000);
    for (int i = 0; i < 100000; ++i) {
        CHECK(singletons[i] == 2 * i);
    }
    CHECK(values.front() == 1000000000 && values.back() == -1000000000);
    std::cout << "Q3 maximum-scale checks passed\n";

    // Q6: maximum target count, every target on the range boundary, late winner.
    std::vector<aim::q6::Target> targets;
    targets.reserve(100000);
    for (int i = 99999; i >= 0; --i) {
        targets.push_back({i, -600000, 800000, 100, true});
    }
    CHECK(aim::q6::select_target(targets, 1000000) == 0);
    CHECK(targets.front().id == 99999 && targets.back().id == 0);
    targets.front().hp = 1;
    CHECK(aim::q6::select_target(targets, 1000000) == 99999);
    targets.front().visible = false;
    CHECK(aim::q6::select_target(targets, 1000000) == 0);
    std::reverse(targets.begin(), targets.end());
    CHECK(aim::q6::select_target(targets, 1000000) == 0);
    CHECK(aim::q6::select_target(targets, 999999) == -1);
    std::cout << "Q6 maximum-scale checks passed\n";

    // Q8: maximum frames, all 10000 IDs in reverse order followed by duplicates.
    std::vector<aim::q8::Telemetry> frames;
    frames.reserve(20000);
    for (int id = 9999; id >= 0; --id) {
        frames.push_back({id, 1000});
    }
    for (int id = 0; id < 10000; ++id) {
        frames.push_back({id, 0});
    }
    const auto summary = aim::q8::summarize(frames);
    CHECK(summary.valid == 10000 && summary.duplicate == 10000 && summary.invalid == 0);
    CHECK(summary.total_hp == 1000000 && summary.ids.size() == 10000);
    for (int id = 0; id < 10000; ++id) {
        CHECK(summary.ids[id] == id);
    }
    CHECK(frames.front().id == 9999 && frames.front().hp == 1000);
    frames.front().hp = 1001;
    const auto invalid_first = aim::q8::summarize(frames);
    CHECK(invalid_first.valid == 10000 && invalid_first.duplicate == 9999
          && invalid_first.invalid == 1 && invalid_first.total_hp == 999900);
    CHECK(invalid_first.valid + invalid_first.duplicate + invalid_first.invalid == 20000);
    CHECK(invalid_first.ids == summary.ids);
    std::cout << "Q8 maximum-scale checks passed\n";

    // B2: 40000 known blocks, retaining {0,2,-1} from each block in that order.
    const int block[] = {3, -2, 0, 2, -1};
    const int expected[] = {0, 2, -1};
    std::vector<int> data(200000);
    for (std::size_t i = 0; i < data.size(); ++i) {
        data[i] = block[i % 5];
    }
    const auto retained = aim::b2::compact(data.data(), data.size(), -1, 2);
    CHECK(retained == 120000);
    for (std::size_t i = 0; i < retained; ++i) {
        CHECK(data[i] == expected[i % 3]);
    }
    std::cout << "B2 maximum-scale checks passed\n";
    std::cout << "Maximum-scale checks passed (Q3, Q6, Q8, B2)\n";
}
