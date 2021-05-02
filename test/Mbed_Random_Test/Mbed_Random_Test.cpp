#include <unity.h>
#include <Arduino.h>
#include "Util/Seed.hpp"

// Seeding must cause RNG to generate new, first random number
void test_seed_unique(void)
{
    uint8_t const analog_in_pin = 0;

    // Prove that random will produce same numbers with same seed
    int rand1, rand2;
    randomSeed(0);
    rand1 = random();

    randomSeed(0);
    rand2 = random();

    TEST_ASSERT_EQUAL(rand1, rand2);

    // Generate seeds
    int seed1, seed2;
    seed1 = generate_seed(analog_in_pin);
    delay(1);
    seed2 = generate_seed(analog_in_pin);

    randomSeed(seed1);
    rand1 = random();

    randomSeed(seed2);
    rand2 = random();

    TEST_ASSERT_NOT_EQUAL_MESSAGE(rand1,
                                  rand2,
                                  "Analog pin used in test LIKELY connected to something (not left floating).");
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_seed_unique);

    UNITY_END();
}