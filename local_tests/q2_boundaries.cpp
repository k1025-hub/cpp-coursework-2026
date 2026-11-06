#define main q2_public_main
#include "../src/main/A1_q2.cpp"
#undef main

int main() {
    // 完整匹配 + 仅首次命中：cam2 不能被修改，第二个 cam 必须保留。
    CHECK(edit_labels("cam2,cam,cam", {{"cam", "camera"}})
          == "cam2,camera,cam");
    // 顺序删除中间、末尾、唯一标签，再从空名单追加。
    CHECK(edit_labels("a,b,c", {{"b", ""}, {"c", ""}, {"a", ""}, {"", "imu"}})
          == "imu");
    // 删除首标签后变长改名，再重新查找；最后两项分别未命中和不操作。
    CHECK(edit_labels("a,b,b", {{"a", ""}, {"b", "long_name"},
                               {"b", "x"}, {"B", "wrong"}, {"", ""}})
          == "long_name,x");
    std::cout << "Q2 boundary checks passed (3 cases)\n";
}
