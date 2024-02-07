#include "../libsrc/BigNum.h"
#include <cstddef>
#include <cstdio>
#include <exception>
#include <functional>
#include <string>
#include <vector>

struct TestSet {
    BigNum a;
    BigNum b;
    BigNum correct_res;
};

class TestError : public std::exception {
  public:
    TestSet test_set;
    BigNum got_res;
    std::string name;
    std::string message;

    TestError(TestSet test_set, BigNum got_res, std::string test_name) {
        this->test_set = test_set;
        this->got_res = got_res;
        this->name = test_name;
        message = name + " " + test_set.a.toString() + " " +
                  test_set.b.toString() + " = " + got_res.toString() +
                  "Expected: " + test_set.correct_res.toString();
    }

    const char *what() const noexcept override { return message.c_str(); }
};

void run_test(std::function<BigNum(BigNum, BigNum)> func,
              std::vector<TestSet> test_sets, std::string name) {
    printf("Testing [%s] ... \n", name.c_str());
    size_t cnt = test_sets.size();
    for (auto &test_set : test_sets) {
        try {
            auto res = func(test_set.a, test_set.b);
            if (res != test_set.correct_res) {
                --cnt;
                throw TestError(test_set, res, name);
            }
            printf("\x1b[32m[OK]\x1b[0m \n");
        } catch (const TestError &e) {
            printf("\x1b[31m[ERROR]: %s \x1b[0m", e.name.c_str());
            printf(" a = %s  b = %s  res = %s | Expected: %s\n",
                   e.test_set.a.toString().c_str(),
                   e.test_set.b.toString().c_str(),
                   e.got_res.toString().c_str(),
                   e.test_set.correct_res.toString().c_str());
        }
    }
    if (cnt < test_sets.size()) {
        printf("\x1b[31mTests block [%s] is NOT PASSED (%lu/%lu tests "
               "passed)\n\n\x1b[0m",
               name.c_str(), cnt, test_sets.size());
    } else {
        printf("\x1b[32mTests block [%s] is PASSED \n\n\x1b[0m", name.c_str());
    }
}

int main() {
    printf("\n");
    run_test([](BigNum a, BigNum b) { return a + b; },
             {{1, 2, 3}, {-1, 2, 1}, {-1, -2, -3}}, "check sum");

    run_test([](BigNum a, BigNum b) { return a - b; },
             {{1, 2, -1}, {-1, 2, -3}, {-1, -2, 1}}, "check subtraction");

    run_test([](BigNum a, BigNum b) { return a * b; },
             {{1, 2, 2}, {10, 0.5, 5}, {-0.2, -2, 0.4}},
             "check multiplication");

    run_test([](BigNum a, BigNum b) { return a / b; },
             {{1, 2, 0.5},
              {10, 0.5, 20},
              {"166350886035.376989", "864847832487", "0.192347"}},
             "check division");

    return 0;
}
