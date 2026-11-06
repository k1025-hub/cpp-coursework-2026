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
    // 空编辑原样返回，同名替换仍只处理一次且不影响下一条编辑。
    CHECK(edit_labels("cam,imu", {}) == "cam,imu");
    CHECK(edit_labels("a,a", {{"a", "a"}, {"a", "x"}}) == "x,a");

    // 空名单可连续追加，允许重复；空名单上的删除未命中不产生逗号。
    CHECK(edit_labels("", {{"", ""}, {"", "imu"}, {"", "imu"}, {"", "lidar"}})
          == "imu,imu,lidar");
    CHECK(edit_labels("", {{"cam", ""}}).empty());

    // 副本与 const 引用的契约：调用方原文本和两条编辑记录均保持不变。
    const std::string labels = "cam,imu";
    const std::vector<LabelEdit> edits{{"cam", "camera"}, {"imu", ""}};
    CHECK(edit_labels(labels, edits) == "camera");
    CHECK(labels == "cam,imu");
    CHECK(edits.size() == 2 && edits[0].from == "cam" && edits[0].to == "camera"
          && edits[1].from == "imu" && edits[1].to.empty());
    std::cout << "Q2 boundary checks passed (original and extended cases)\n";
}
