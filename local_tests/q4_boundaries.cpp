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
    // 参数超界与运算结果超界是两项独立检查；合法负端点仍应接受。
    const auto argument_limits = execute({"SET 17", "SET 1000001", "ADD -1000001",
                                          "SET 9223372036854775807",
                                          "ADD -9223372036854775808", "SET -1000000"});
    CHECK(argument_limits.value == -1000000 && argument_limits.accepted == 2
          && argument_limits.rejected == 4);

    // 缺参、额外参数、全空白、非十进制尾缀均拒绝；标准流空白可接受。
    const std::vector<std::string> malformed{"SET 23", "ADD 1 2", "SET 4 5", "RESET 0",
        "SET", " \t\r\n", "ADD 0x10", "ADD 1e2", "RESET\t\v\f\r\n"};
    const auto strict = execute(malformed);
    CHECK(strict.value == 0 && strict.accepted == 2 && strict.rejected == 7);
    CHECK(strict.accepted + strict.rejected == static_cast<int>(malformed.size()));
    CHECK(malformed[0] == "SET 23" && malformed[1] == "ADD 1 2");

    // 先固定一个非零值，再逐条核对每次拒绝都不改变状态。
    const std::vector<std::string> invalid_commands{"SET 1000001", "ADD -1000001",
        "SET 8 extra", "RESET 1", "ADD +", "reset"};
    for (const std::string& command : invalid_commands) {
        const auto unchanged = execute({"SET 23", command});
        CHECK(unchanged.value == 23 && unchanged.accepted == 1 && unchanged.rejected == 1);
    }
    std::cout << "Q4 boundary checks passed (original and extended cases)\n";
}
