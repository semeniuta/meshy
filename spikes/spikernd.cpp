/**
 * Play around with random number generation.
 */

#include <iostream>
#include <random>

int main() {

    std::random_device rd{};

    std::default_random_engine generator{rd()};
    generator.seed(42);

    std::uniform_int_distribution<int> distrib{0, 100};

    for (int i = 0; i < 10; i++) {
        int rnum = distrib(generator);

        std::cout << rnum << std::endl;
    }



}