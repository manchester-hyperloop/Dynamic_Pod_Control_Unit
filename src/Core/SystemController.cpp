//
//  SystemController.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef UNIT_TEST
#include <Arduino.h>
#endif

#include "Core/SystemController.hpp"
#include "Core/Mode/ModeHeader.hpp"

using namespace Core;

SystemController::SystemController() : activeMode(nullptr), nextMode(nullptr)
{
}

SystemController &SystemController::getSysCtrlInstance()
{
    static SystemController instance;
    return instance;
}

bool SystemController::init(Mode::Mode *initialMode)
{
    // Do not initialise twice
    if (initialised)
        return false;

#ifndef UNIT_TEST

    // Everything's working correctly
    Serial.println("System controller is alive!");
#endif

    // Set the initial mode
    nextMode = initialMode;

    // set ctrl state to initialised
    initialised = true;

    return true;
}

bool SystemController::run()
{
    // do not run if we're not initialised
    if (!initialised)
        return false;

    // See if we should transition to a new mode
    if (nextMode != nullptr)
    {
        bool transitionSuccess = transitionToNextMode();
        if (!transitionSuccess)
        {
            return false;
        }
    }

    // execute the defined behaviour for the current mode
    if (activeMode != nullptr)
        activeMode->run();

    return true;
}

void SystemController::resetInstance()
{
    initialised = false;
    activeMode = nullptr;
    nextMode = nullptr;
}

void SystemController::shouldTransitionToMode(Mode::ModeType newMode)
{
    switch (newMode)
    {
#ifdef UNIT_TEST
    case Mode::TEST:
        nextMode = new Mode::ModeTest(this);
        break;
#endif
    default:
        nextMode = nullptr;
    }
}

bool SystemController::transitionToNextMode()
{
    // delete active mode
    delete activeMode;

    // transition the 'next mode' to active mode
    activeMode = nextMode;
    nextMode = nullptr;

    // Initialise the new active mode
    bool initSuccess = activeMode->init();
    if (!initSuccess)
    {
        return false;
    }

    return true;
}

Mode::Mode *SystemController::getCurrentlyActiveMode()
{
    return activeMode;
}
