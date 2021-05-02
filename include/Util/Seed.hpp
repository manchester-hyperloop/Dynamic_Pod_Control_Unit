#ifndef UTIL_SEED_HPP
#define UTIL_SEED_HPP

#ifndef UNIT_TEST
#include <Arduino.h>

// Randomly generates a seed for the random number generator
int generate_seed(uint8_t const analog_pin)
{
    int seed = 0;
    int bit = 1;

    while (bit)
    {
        byte a = analogRead(analog_pin);
        delay(1);
        byte b = analogRead(analog_pin);
        delay(1);

        // if the LSb are not the same
        if ((a & 1) != (b & 1))
        {
            if (a & 1)
                seed |= bit;
            bit <<= 1;
        }
    }

    return seed;
}

#endif

#endif /* UTIL_SEED_HPP */