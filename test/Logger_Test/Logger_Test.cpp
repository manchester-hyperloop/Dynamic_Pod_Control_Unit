//
//  Logger_Test.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#include <unity.h>
#include <Log.hpp>

void setup(void) {

}

void tearDown(void) {
    Log &instance = Log::getLogger();
    instance.resetInstance();
}


// Log should only accessible through a static 'getter' method
void test_get_log_instance(void)
{
    Log &instance = Log::getLogger();
    TEST_ASSERT(instanceof <Log>(&instance));
}

// System Controller should be a singleton and only have 1 instance in memory
void test_log_singleton(void)
{
    // Get two instances
    Log &instance1 = Log::getLogger();
    Log &instance2 = Log::getLogger();

    // Modify one of them
    int const testVal = 10;
#ifdef UNIT_TEST //Always true here (cause this is a test)
    instance1.setTestValue(testVal);

    // Test if the other has been changed
    TEST_ASSERT(instance2.getTestValue() == testVal);
#endif
}

// System Controller should not run if not initialised properly
void test_system_controller_initialise(void)
{
    Core::SystemController &sysCtrl = Core::SystemController::getSysCtrlInstance();

    // Try running before not being initialised
    TEST_ASSERT_FALSE(sysCtrl.run());

    // Now initialise and try again!
    sysCtrl.init(nullptr);
    TEST_ASSERT(sysCtrl.run());
}

// System Controller must verify that it is initialised
void test_system_controller_is_initialised(void)
{
    Core::SystemController &sysCtrl = Core::SystemController::getSysCtrlInstance();

    // Check if initialised
    TEST_ASSERT_FALSE(sysCtrl.isInitialised());

    // Now initialise and try again!
    sysCtrl.init(nullptr);
    TEST_ASSERT(sysCtrl.isInitialised());
}

void test_sys_controller_cant_initialise_twice(void)
{
    Core::SystemController &sysCtrl = Core::SystemController::getSysCtrlInstance();

    // Initialise
    TEST_ASSERT(sysCtrl.init(nullptr));
    TEST_ASSERT(sysCtrl.isInitialised());

    // Check if we can do it twice (we shouldn't be able to -> hence expect false)
    TEST_ASSERT_FALSE(sysCtrl.init(nullptr));
}

int main(int argc, char** argv) {
    UNITY_BEGIN();



    UNITY_END();
}