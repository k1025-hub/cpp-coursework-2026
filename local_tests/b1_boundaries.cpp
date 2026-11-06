#define main b1_public_main
#include "../src/main/A1_b1.cpp"
#undef main

int main() {
    // 第 1 组：正负端点和各自越界一位，失败保护输出。
    int value = 9;
    CHECK(parse_i32("2147483647", value) && value == 2147483647);
    CHECK(parse_i32("-2147483648", value) && value == (-2147483647 - 1));
    CHECK(!parse_i32("2147483648", value) && value == (-2147483647 - 1));
    CHECK(!parse_i32("-2147483649", value) && value == (-2147483647 - 1));

    // 第 2 组：严格 ASCII 语法，包括嵌入空字符，均不修改输出。
    const std::vector<std::string> invalid{"", "+", "-", " 1", "1 ", "\t1",
        "1.0", "1e2", "++1", "--1", "+-1", "12x", "１２", std::string("1\0", 2)};
    for (const std::string& text : invalid) {
        value = 73;
        CHECK(!parse_i32(text, value) && value == 73);
    }

    // 第 3 组：有符号零、前导零、1000 位数字的溢出与合法情况。
    CHECK(parse_i32("+0", value) && value == 0);
    CHECK(parse_i32("-0000", value) && value == 0);
    CHECK(parse_i32("+00042", value) && value == 42);
    CHECK(!parse_i32(std::string(1000, '9'), value) && value == 42);
    CHECK(parse_i32(std::string(1000, '0'), value) && value == 0);
    CHECK(parse_i32(std::string(999, '0') + "1", value) && value == 1);
    std::cout << "B1 boundary checks passed (3 groups)\n";
}
