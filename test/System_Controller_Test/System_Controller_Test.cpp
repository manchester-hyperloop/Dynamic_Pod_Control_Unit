//
//  System_Controller_Test.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#include <unity.h>
#include "Core/SystemController.hpp"
#include <Mode_Mock.hpp>
#include <Instance.hpp>

void setup(void)
{
}

void tearDown(void)
{
    Core::SystemController &instance = Core::SystemController::getInstance();
    instance.reset();
}

// System Controller should only accessible through a static 'getter' method
void test_get_sys_ctrl_instance(void)
{
    Core::SystemController &instance = Core::SystemController::getInstance();

    TEST_ASSERT(instanceof <Core::SystemController>(&instance));
}

// System Controller should be a singleton and only have 1 instance in memory
void test_sys_ctrl_singleton(void)
{
    // Get two instances
    Core::SystemController &instance1 = Core::SystemController::getInstance();
    Core::SystemController &instance2 = Core::SystemController::getInstance();

    // Modify one of them
    const int testVal = 10;
#ifdef UNIT_TEST //Always true here (cause this is a test)
    instance1.setTestValue(testVal);

    // Test if the other has been changed
    TEST_ASSERT(instance2.getTestValue() == testVal);
#endif
}

// System Controller should not run if not initialised properly
void test_system_controller_initialise(void)
{
    Core::SystemController &sysCtrl = Core::SystemController::getInstance();

    // Try running before not being initialised
    TEST_ASSERT_FALSE(sysCtrl.run());

    // Now initialise and try again!
    sysCtrl.init(Core::Mode::MODE_ID_TEST);
    TEST_ASSERT(sysCtrl.run());
}

// System Controller must verify that it is initialised
void test_system_controller_is_initialised(void)
{
    Core::SystemController &sysCtrl = Core::SystemController::getInstance();

    // Check if initialised
    TEST_ASSERT_FALSE(sysCtrl.isInitialised());

    // Now initialise and try again!
    sysCtrl.init(Core::Mode::MODE_ID_TEST);
    TEST_ASSERT(sysCtrl.isInitialised());
}

void test_sys_controller_cant_initialise_twice(void)
{
    Core::SystemController &sysCtrl = Core::SystemController::getInstance();

    // Initialise
    TEST_ASSERT(sysCtrl.init(Core::Mode::MODE_ID_TEST));
    TEST_ASSERT(sysCtrl.isInitialised());

    // Check if we can do it twice (we shouldn't be able to -> hence expect false)
    TEST_ASSERT_FALSE(sysCtrl.init(Core::Mode::MODE_ID_TEST));
}

// System controller should be able to take a 'Mode' as a variable to define the system's behaviour and change between modes if requested
void test_change_between_modes(void)
{
    Core::SystemController &sysCtrl = Core::SystemController::getInstance();
    sysCtrl.init(Core::Mode::MODE_ID_TEST);
    sysCtrl.run();

    const Core::Mode::ModeTest *state = (Core::Mode::ModeTest*)sysCtrl.getModeById(Core::Mode::MODE_ID_TEST);

    TEST_ASSERT_NOT_NULL(state);
    TEST_ASSERT(state->wasInitialised());
    TEST_ASSERT(state->wasExecuted());
}

// System controller should not change to a new mode if not requested
// FIXME: need to consider whether this test is even valid anymore
void test_no_change_if_no_request(void)
{
    /*
    Core::SystemController &sysCtrl = Core::SystemController::getInstance();
    sysCtrl.init(Core::Mode::MODE_ID_TEST);
    sysCtrl.run();

    TEST_ASSERT(testMode.wasInitialised());
    TEST_ASSERT(testMode.wasExecuted());

    sysCtrl.run();

    TEST_ASSERT(testMode.getTimesExecuted() == 2);
    */
}

// System controller should run the behaviour of the 'active' mode
// FIXME: need to rewrite this test to handle new behaviour
void test_run_active_mode(void)
{
    /*
    Core::SystemController &sysCtrl = Core::SystemController::getInstance();
    sysCtrl.init(Core::Mode::MODE_ID_TEST);
    sysCtrl.run();

    TEST_ASSERT(testMode1->wasInitialised());
    TEST_ASSERT(testMode1->wasExecuted());

    testMode1->transitionToNextTestMock();

    TEST_ASSERT(sysCtrl.run());

    Core::Mode::ModeTest *testMode2 = (Core::Mode::ModeTest *)sysCtrl.getCurrentlyActiveMode();
    TEST_ASSERT(testMode2->getTimesExecuted() == 1);
    */
}

int main(int argc, char **argv)
{

    UNITY_BEGIN();

    RUN_TEST(test_get_sys_ctrl_instance);
    RUN_TEST(test_sys_ctrl_singleton);
    RUN_TEST(test_system_controller_initialise);
    RUN_TEST(test_system_controller_is_initialised);
    RUN_TEST(test_sys_controller_cant_initialise_twice);
    RUN_TEST(test_change_between_modes);
    RUN_TEST(test_no_change_if_no_request);
    RUN_TEST(test_run_active_mode);

    UNITY_END();
    return 0;
}