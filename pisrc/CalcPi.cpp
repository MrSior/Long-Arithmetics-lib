#include "CalcPi.h"

BigNum CalcPi(int32_t precision) {
    ++precision;

    auto math_sqrt = [](const BigNum &num) {
        BigNum lh = 0;
        BigNum rh = num + 1;
        BigNum eps = 1;
        eps.setExp(-70);
        while (rh - lh > eps) {
            auto mid = lh + (rh - lh) * 0.5;

            if (mid * mid < num) {
                lh = mid;
            } else {
                rh = mid;
            }
        }
        return lh + (rh - lh) * 0.5;
    };

    auto sqrt = [&math_sqrt](const BigNum &n, const BigNum &one) {
        BigNum floating_point_precision = "10000000000000000";
        auto n_float = BigNumDiv(n * floating_point_precision, one, 0) /
                       floating_point_precision;
        auto tmp = (floating_point_precision * math_sqrt(n_float) * one);
        tmp.evalf(0);
        auto x = BigNumDiv(tmp, floating_point_precision, 0);
        auto n_one = n * one;
        while (1) {
            auto x_old = x;
            x = BigNumDiv(x + BigNumDiv(n_one, x, 0), 2, 0);
            if (x == x_old) {
                break;
            }
        }
        return x;
    };

    BigNum C = 640320;
    BigNum C3_OVER_24 = "10939058860032000";

    struct triple {
        BigNum first;
        BigNum second;
        BigNum third;
    };

    std::function<triple(int64_t, int64_t)> bs;
    bs = [&bs, &C3_OVER_24](const int64_t &a, const int64_t &b) -> triple {
        BigNum Pab = 0;
        BigNum Qab = 0;
        BigNum Tab = 0;
        if (b - a == 1) {
            if (a == 0) {
                Pab = Qab = 1;
            } else {
                Pab = (6 * a - 5) * (2 * a - 1) * (6 * a - 1);
                Qab = a * a * a * C3_OVER_24;
            }
            Tab = Pab * (13591409 + 545140134 * a);
            if (a & 1) {
                Tab.setSign(Tab.getSign() * -1);
            }
        } else {
            int64_t m = (a + b) / 2;
            auto res_a = bs(a, m);
            auto res_b = bs(m, b);
            Pab = res_a.first * res_b.first;
            Qab = res_a.second * res_b.second;
            Tab = res_b.second * res_a.third + res_a.first * res_b.third;
        }

        triple res = {Pab, Qab, Tab};
        return res;
    };

    BigNum digits_per_term =
        "14.181647462725477655525521678181770863769125289828726959816854332";
    int64_t n = static_cast<int>(precision / 14.1816474627 + 1);
    auto res = bs(0, n);

    BigNum one = 1;
    for (int i = 0; i < precision; ++i) {
        one = one * 10;
    }

    auto sqrtC = sqrt(10005 * one, one);
    auto r = res.second * sqrtC * 426880;
    auto pi = BigNumDiv(r, res.third, 0);

    auto pi_str = pi.toString();
    while (pi_str.length() > precision) {
        pi_str.pop_back();
    }
    pi = BigNum(pi_str);
    pi.setExp(pi.getExp() - (pi_str.length()) + 1);

    return pi;
}
