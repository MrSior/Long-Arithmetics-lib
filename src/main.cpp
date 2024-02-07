#include "../libsrc/BigNum.h"
#include <iostream>

using namespace std::chrono;

int main() {
    BigNum a = "10";
    //    BigNum a = "0.192347";
    a.printBlocks();
    BigNum b = "0.5";
    b.printBlocks();

    std::cout << (a / b).toString() << std::endl;

    // std::cout << (BigNum("0.5") * BigNum("2.0") <= BigNum("2.5"));

    auto time_s = high_resolution_clock::now();
    std::cout << CalcPi(100).toString() << std::endl;
    auto time_end = high_resolution_clock::now();
    std::cout << "Time: "
              << duration_cast<milliseconds>(time_end - time_s).count()
              << " milliseconds" << std::endl;

    printf("\x1b[42m[OK]\x1b[0m  \n");
    printf("\x1b[37;41m[ERROR]\x1b[0m  \n");
    return 0;
}
