//
//  TestCallbackFunctions.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef TEST_CALLBACK_FUNCTIONS
#define TEST_CALLBACK_FUNCTIONS

static bool functionHasExecuted;

static void myTestFunction()
{
    functionHasExecuted = true;
}

static void myTestFunctionWithParam(bool is_successful)
{
    functionHasExecuted = is_successful;
}

struct MyTestStruct
{
    void myTestMethod()
    {
        functionHasExecuted = true;
    }

    void myTestMethodWithParam(bool is_successful)
    {
        functionHasExecuted = is_successful;
    }
};

#endif /* TEST_CALLBACK_FUNCTIONS */