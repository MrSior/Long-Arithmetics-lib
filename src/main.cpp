#include "../libsrc/BigNum.h"
#include <iostream>

using namespace std::chrono;

int main() {
    //    BigNum a = "000000166350886035.37698900000";
    ////    BigNum a = "0.192347";
    //    a.printBlocks();
    //    BigNum b = "864847832487";
    //    b.printBlocks();
    //
    //    std::cout << (a / b).toString();
    auto time_s = high_resolution_clock::now();
    std::cout << CalcPi(100).toString() << std::endl;
    auto time_end = high_resolution_clock::now();
    std::cout << "Time: "
              << duration_cast<milliseconds>(time_end - time_s).count()
              << " milliseconds" << std::endl;

    return 0;
}
