#define main q4_public_main
#include "../src/main/A1_q4.cpp"
#undef main

int main() {
    // 第 1 组：参数合法但候选结果超界；非法 RESET 不能清零。
    const auto limits = execute({"SET 1000000", "ADD 1", "SET -1000000",
                                 "ADD -1", "ADD 999999", "RESET x"});
    CHECK(limits.value == -1 && limits.accepted == 3 && limits.rejected == 3);

    // 第 2 组：提取出的数字不等于整行合法，失败不能改变已有值。
    const auto syntax = execute({"SET 5", "ADD 1.5", "SET 8x", "ADD",
                                 "SET 999999999999999999999999", "add 1", "RESET x", ""});
    CHECK(syntax.value == 5 && syntax.accepted == 1 && syntax.rejected == 7);

    // 第 3 组：流空白、正号、前导零合法，各次调用独立。
    const auto whitespace = execute({"\tSET +0007 \r", " ADD -2\n", "RESET ", "ADD +1"});
    CHECK(whitespace.value == 1 && whitespace.accepted == 4 && whitespace.rejected == 0);
    const auto empty = execute({});
    CHECK(empty.value == 0 && empty.accepted == 0 && empty.rejected == 0);
    std::cout << "Q4 boundary checks passed (3 groups)\n";
}
