#ifndef UTIL_SEED_HPP
#define UTIL_SEED_HPP

#ifndef UNIT_TEST
#include <Arduino.h>

int getSeed()
{
    // Run the seeding algo
    int seed = 0;
    int bit = 1;

    while (bit)
    {
        byte a = analogRead(0);
        delay(1);
        byte b = analogRead(0);
        delay(1);

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