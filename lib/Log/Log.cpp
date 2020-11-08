//
//  Log.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#include "Log.hpp"

#ifndef UNIT_TEST
#include <Arduino.h>
#endif

void Log::init()
{
#ifndef UNIT_TEST
    randomSeed(random());
#endif
}

Log &Log::getInstance()
{
    static Log log;
    return log;
}

void Log::resetInstance()
{
    setFileName(nullptr);
}

void Log::operator()(const char *message, int parameter, const char *fileName, int line)
{
    // LOG Message
}

void Log::setFileName(char *newName)
{
    // close file if open
    // ...

    // update stored name
    fileName = newName;

    //Attempt to open/create new file
    // ...
}