#include "../libsrc/BigNum.h"
#include <iostream>

using namespace std::chrono;

int main() {
    // BigNum a = "166350886035.376989";
    // //    BigNum a = "0.192347";
    // // a.printBlocks();
    // BigNum b = "864847832487";
    // // b.printBlocks();

    // std::cout << (a / b).toString() << std::endl;

    // LOG (BINSEARCH): lh = 8	mid = 9	rh = 10.000
    // LOG (oper <): 864847832487 < 9 = 0
    // LOG (oper <): 7986610278667.6989 < 7783630492383 = 0
    // LOG (oper <): 864847832487 < 9 = 0
    // LOG (oper <): 7783630492383 < 7986610278667.6989 = 0
    // LOG (oper <): 1 < 2.000 = 1
    // LOG (oper <): 2.000 < 0.5 = 0

    BigNum a = "1";
    BigNum b = "2";
    std::cout << CalcPi(10).toString();
    return 0;
}
