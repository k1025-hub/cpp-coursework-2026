#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 B1; see 题面.pdf.
namespace aim::b1 {


// BEGIN IMPLEMENTATION
// aim-cpp-cw
bool parse_i32(const std::string& text, int& output) {
    if (text.empty()) {
        return false;
    }
    std::size_t position = 0;
    bool negative = false;
    if (text[0] == '+' || text[0] == '-') {
        negative = text[0] == '-';
        position = 1;
    }
    if (position == text.size()) {
        return false;
    }

    // 负数端点的绝对值比正数端点大 1，使用 long long 保存幅值。
    const long long limit = negative ? 2147483648LL : 2147483647LL;
    long long magnitude = 0;
    for (; position < text.size(); ++position) {
        const char character = text[position];
        if (character < '0' || character > '9') {
            return false;
        }
        const int digit = character - '0';
        // 先判断下一步是否超界，再执行乘法和加法。
        if (magnitude > (limit - digit) / 10) {
            return false;
        }
        magnitude = magnitude * 10 + digit;
    }
    const long long value = negative ? -magnitude : magnitude;
    output = static_cast<int>(value); // 只有全部验证成功才改写输出。
    return true;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::b1;
int main() {
    try {
        { int x=9; CHECK(parse_i32("-12",x) && x==-12); }
        { int x=9; CHECK(!parse_i32("12x",x) && x==9); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
