//
//  Logger_Test.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#include <unity.h>
// #include <Log.hpp>

void setup(void)
{
}

void tearDown(void)
{
    // Log &instance = Log::getLogger();
    // instance.resetInstance();
}

// Log should only accessible through a static 'getter' method
void test_get_log_instance(void)
{
    // Log &instance = Log::getLogger();
    // TEST_ASSERT(instanceof <Log>(&instance));
}

// System Controller should be a singleton and only have 1 instance in memory
void test_log_singleton(void)
{
    //     // Get two instances
    //     Log &instance1 = Log::getLogger();
    //     Log &instance2 = Log::getLogger();

    //     // Modify one of them
    //     int const testVal = 10;
    // #ifdef UNIT_TEST //Always true here (cause this is a test)
    //     instance1.setTestValue(testVal);

    //     // Test if the other has been changed
    //     TEST_ASSERT(instance2.getTestValue() == testVal);
    // #endif
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    UNITY_END();
}