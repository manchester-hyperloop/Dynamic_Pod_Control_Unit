//
//  CallbackTest.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#include <unity.h>
#include <iostream>
#include <Callback.hpp>
#include "TestCallbackFunctions.hpp"

void setup(void)
{
    functionHasExecuted = false;
}

void tearDown(void)
{
}

// Callback must be able to execute a function, passed to it, at a later time
void test_pass_function_to_cb(void)
{
    setup();

    Callback<void> *cb = new FuncCallback<void>(&myTestFunction);
    cb->run();

    TEST_ASSERT_TRUE(functionHasExecuted);
}

// A callback must be able to take a method of an instantiated class
void test_pass_method_to_cb(void)
{
    setup();

    MyTestStruct test_struct;

    Callback<void> *cb = new MethodCallback<MyTestStruct, void>(&MyTestStruct::myTestMethod, &test_struct);
    cb->run();

    TEST_ASSERT_TRUE(functionHasExecuted);
}

// Callback must not execute a function that does not exist in memory (is null)
void test_func_null(void)
{
    setup();

    Callback<void> *cb = new FuncCallback<void>(nullptr);
    cb->run();
    // TODO: Do NOT fail silently
}

// Callback must not execute a method that does not exist in memory (is null)
void test_class_is_null(void)
{
    // TODO: Do NOT fail silently
    Callback<void> *cb = new MethodCallback<MyTestStruct, void>(nullptr, nullptr);
}

// Callback must not execute a method that does not exist in memory (Has gone out of scope)
void test_class_out_of_scope(void)
{
    setup();

    // Initialise the test struct
    MyTestStruct *test_struct = new MyTestStruct();

    // Pass one of it's methods to the CB
    Callback<void> *cb = new MethodCallback<MyTestStruct, void>(&MyTestStruct::myTestMethod, test_struct);

    // Delete the struct (to remove it from memory)
    delete test_struct;

    // Test if we crash, and/or successfully notice that the struct no longer exists
    // TODO: Do NOT fail silently
    cb->run();
}

// A callback to a function can have 1 parameter of arbitrary type
void test_callback_func_param(void)
{
    setup();

    Callback<bool> *cb = new FuncCallback<bool>(&myTestFunctionWithParam);
    cb->run(true);

    TEST_ASSERT_TRUE(functionHasExecuted);
}

// A callback to a method can have 1 parameter of arbitrary type
void test_callback_method_param(void)
{
    setup();

    MyTestStruct test_struct;

    Callback<bool> *cb = new MethodCallback<MyTestStruct, bool>(&MyTestStruct::myTestMethodWithParam, &test_struct);
    cb->run(true);

    TEST_ASSERT_TRUE(functionHasExecuted);
}

// A callback can have any number of parameters of arbitrary type
// void test_callback_method_multi_params(void)
// {
//     TEST_FAIL_MESSAGE("No test here yet!");
// }

// A callback can have any number of parameters of arbitrary type
// void test_callback_func_multi_params(void)
// {
//     TEST_FAIL_MESSAGE("No test here yet!");
// }

int main(int argc, char **argv)
{

    UNITY_BEGIN();

    RUN_TEST(test_pass_function_to_cb);
    RUN_TEST(test_pass_method_to_cb);

    RUN_TEST(test_func_null);
    RUN_TEST(test_class_is_null);
    // RUN_TEST(test_class_out_of_scope);

    RUN_TEST(test_callback_func_param);
    RUN_TEST(test_callback_method_param);
    // RUN_TEST(test_callback_func_multi_params);
    // RUN_TEST(test_callback_method_multi_params);

    UNITY_END();
    return 0;
}