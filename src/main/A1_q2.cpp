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

// Assessment 01 Q2; see 题面.pdf.
namespace aim::q2 {
struct LabelEdit { std::string from; std::string to; };

// BEGIN IMPLEMENTATION
// aim-cpp-cw
std::string edit_labels(std::string labels, const std::vector<LabelEdit>& edits) {
    for (const LabelEdit& edit : edits) {
        if (edit.from.empty()) {
            if (!edit.to.empty()) {
                if (!labels.empty()) {
                    labels += ',';
                }
                labels += edit.to;
            }
            continue;
        }

        std::size_t start = 0;
        while (start < labels.size()) {
            const std::size_t comma = labels.find(',', start);
            const std::size_t end = comma == std::string::npos
                                  ? labels.size() : comma;
            const std::size_t length = end - start;

            // 比较整个标签，避免将 cam 匹配到 cam2。
            const bool matches = labels.substr(start, length) == edit.from;
            if (matches) {
                if (!edit.to.empty()) {
                    labels.replace(start, length, edit.to);
                } else if (start == 0) {
                    if (comma != std::string::npos) {
                        labels.erase(0, comma + 1);
                    } else {
                        labels.clear();
                    }
                } else {
                    // 连同当前标签前面的逗号一起删除。
                    labels.erase(start - 1, length + 1);
                }
                break; // 一条编辑只处理第一次命中。
            }

            if (comma == std::string::npos) {
                break;
            }
            start = comma + 1;
        }
    }
    return labels;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q2;
int main() {
    try {
        { CHECK(edit_labels("cam,imu,radar",{{"imu","gyro"},{"cam",""},{"","lidar"}})=="gyro,radar,lidar"); }
        { CHECK(edit_labels("cam,cam2,cam",{{"cam","camera"},{"cam",""}})=="camera,cam2"); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
