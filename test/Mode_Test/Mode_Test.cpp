//
//  Mode_Test.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#include <unity.h>
#include "Core/SystemController.hpp"
#include <Mode_Mock.hpp>

// Mode should not execute 'run' before an initialisation function before executing its main loop
void test_mode_initialisation(void)
{
    TEST_FAIL();
}

// A Mode should not fail silently on initialisation
void init_does_not_fail_silently(void)
{
    TEST_FAIL();
}

// A mode should not fail silently when running
void run_does_not_fail_silently(void)
{
    TEST_FAIL();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    // RUN_TEST(test_mode_initialisation);
    // RUN_TEST(init_does_not_fail_silently);
    // RUN_TEST(run_does_not_fail_silently);

    UNITY_END();
}