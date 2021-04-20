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

Mode::ModeIdle stateIdle;
Mode::ModeAccel stateAccel;
Mode::ModeSteady stateSteady;
Mode::ModeDecel stateDecel;
Mode::ModePanic statePanic;
#ifdef UNIT_TEST
Mode::ModeTest stateTest;
#endif

#ifdef UNIT_TEST
Mode::Mode *states[] = {
    [Mode::MODE_ID_IDLE] = &stateIdle,
    [Mode::MODE_ID_ACCEL] = &stateAccel,
    [Mode::MODE_ID_STEADY] = &stateSteady,
    [Mode::MODE_ID_DECEL] = &stateDecel,
    [Mode::MODE_ID_PANIC] = &statePanic,
    [Mode::MODE_ID_TEST] = &stateTest,
};
#else
Mode::Mode *states[] = {
    [Mode::MODE_ID_IDLE] = &stateIdle,
    [Mode::MODE_ID_ACCEL] = &stateAccel,
    [Mode::MODE_ID_STEADY] = &stateSteady,
    [Mode::MODE_ID_DECEL] = &stateDecel,
    [Mode::MODE_ID_PANIC] = &statePanic,
};
#endif

SystemController::SystemController()
    : previousMode(Mode::MODE_ID_IDLE),
      currentMode(Mode::MODE_ID_IDLE)
{
}

SystemController &SystemController::getInstance()
{
    static SystemController instance;

    return instance;
}

bool SystemController::init(const Mode::MODE_ID initialMode)
{
    // do not initialise twice
    // TODO: would it be better to return true and silently ignore the error,
    // or return a dedicated Error enum? imo calling init multiple times isnt
    // an error, its just wasted work and thus shouldnt "fail" per-se
    if (initialised)
        return false;

#ifdef HAS_CAN_BUS
    // initialise the can bus
    if (!can_bus.init())
        return false;
#endif

    previousMode = initialMode;
    currentMode = initialMode;

    // set ctrl state to initialised
    initialised = true;

    // everything's working correctly
    LOG("System controller was initialised!");

    return true;
}

void SystemController::finalise()
{
    LOG("System controller was finalised!");
}

bool SystemController::run()
{
    // do not run if initialisation failed
    if (!initialised)
        return false;

    bool panicked = false;

    states[currentMode]->setup(this);

    while (1) {
        const Mode::MODE_ID nextMode = states[currentMode]->tick(this);

        if (nextMode == Mode::MODE_FINALISE)
            break;

        // if we ever encounter the panic state, we know that an unrecoverable
        // error has occured, and thus the system state is unsafe. the panic
        // mode should eventually allow finalise to run (and never switch to
        // any other mode), but we need to set the flag to track this
        // "state poisoning" so that the caller of run can handle this case
        if (nextMode == Mode::MODE_ID_PANIC)
            panicked = true;

        // TODO: make atomic by disabling interrupts during the switchover?
        if (nextMode != previousMode) {
            states[currentMode]->teardown(this);
            states[nextMode]->setup(this);

            previousMode = currentMode;
            currentMode = nextMode;
        }
    }

    states[currentMode]->teardown(this);

    return !panicked;
}

void SystemController::reset()
{
    initialised = false;

    previousMode = Mode::MODE_ID_IDLE;
    currentMode = Mode::MODE_ID_IDLE;
}

const Mode::Mode *SystemController::getPreviousMode() const
{
    return states[previousMode];
}

const Mode::Mode *SystemController::getCurrentMode() const
{
    return states[currentMode];
}

const Mode::Mode *SystemController::getModeById(const Mode::MODE_ID id) const
{
    return states[id];
}
