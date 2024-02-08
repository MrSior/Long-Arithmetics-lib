#include "../libsrc/BigNum.h"
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <string>

using namespace std::chrono;

int main() {
    std::string pi =
        "3."
        "1415926535897932384626433832795028841971693993751058209749445923078164"
        "0628620899862803482534211706798214808651328230664709384460955058223172"
        "5359408128481117450284102701938521105559644622948954930381964428810975"
        "6659334461284756482337867831652712019091456485669234603486104543266482"
        "1339360726024914127372458700660631558817488152092096282925409171536436"
        "7892590360011330530548820466521384146951941511609433057270365759591953"
        "0921861173819326117931051185480744623799627495673518857527248912279381"
        "8301194912983367336244065664308602139494639522473719070217986094370277"
        "0539217176293176752384674818467669405132000568127145263560827785771342"
        "7577896091736371787214684409012249534301465495853710507922796892589235"
        "4201995611212902196086403441815981362977477130996051870721134999999837"
        "2978049951059731732816096318595024459455346908302642522308253344685035"
        "2619311881710100031378387528865875332083814206171776691473035982534904"
        "2875546873115956286388235378759375195778185778053217122680661300192787"
        "66111959092164201989";

    printf("Testing [calcPi function] ...\n");

    auto check = [&pi](int digits) {
        auto time_s = high_resolution_clock::now();
        auto res = CalcPi(digits);
        auto time_end = high_resolution_clock::now();
        auto res_str = res.toString();
        int64_t duration = duration_cast<seconds>(time_end - time_s).count();

        auto right_res_str = pi.substr(0, digits + 2);
        while (right_res_str.back() == '0') {
            right_res_str.pop_back();
        }

        if (right_res_str == res_str) {
            printf("\x1b[32m[OK] \x1b[0m digits: %d time: %lld seconds\n",
                   digits, duration);
            return true;
        }
        printf("Right %s\n", right_res_str.c_str());
        printf("My    %s\n", res_str.c_str());
        printf("Exp   %lu\n", res.toString().length());
        printf("\x1b[31m[ERROR]:\x1b[0m digits: %d\n", digits);
        return false;
    };

    for (auto digits : {10, 40, 50, 70, 100}) {
        if (!check(digits)) {
            // return 0;
        }
    }

    return 0;
}
