#define main q1_public_main
#include "../src/main/A1_q1.cpp"
#undef main

int main() {
    CHECK(ratio(-5, 100) == 0);
    CHECK(ratio(200, 100) == 100);
    CHECK(ratio(10, 0) == -1);
    CHECK(ratio(10, -1) == -1);
    CHECK(ratio(999999999999LL, 1000000000000LL) == 99);
    CHECK(ratio(1000000000000LL, 1000000000000LL) == 100);
    CHECK(report(0, 4, 0, -7) == "ID=0;HP=INVALID;BAT=0;STATE=LOW");
    CHECK(report(1, 1, 1, 19) == "ID=1;HP=100;BAT=19;STATE=LOW");
    CHECK(report(1, 1, 1, 20) == "ID=1;HP=100;BAT=20;STATE=WARNING");
    CHECK(report(1, 1, 1, 59) == "ID=1;HP=100;BAT=59;STATE=WARNING");
    CHECK(report(1, 1, 1, 60) == "ID=1;HP=100;BAT=60;STATE=OK");
    CHECK(report(9999, 1, 1, std::numeric_limits<int>::max())
          == "ID=9999;HP=100;BAT=100;STATE=OK");
    CHECK(report(0, 1, 1, std::numeric_limits<int>::min())
          == "ID=0;HP=100;BAT=0;STATE=LOW");
    std::cout << "Q1 boundary checks passed (13 checks)\n";
}
