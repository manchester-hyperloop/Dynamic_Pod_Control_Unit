//
//  SystemController.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef CORE_SYSTEM_CONTROLLER_HPP
#define CORE_SYSTEM_CONTROLLER_HPP

#include "Mode/ModeType.hpp"
#include "Mode/Mode.hpp"

// TODO: Initialise timestamp on first load
// Probs best to do this with onboard EEPROM

namespace Core
{
    class SystemController
    {
        bool initialised = false;

        Mode::Mode *activeMode;
        Mode::Mode *nextMode;

    public:
        /**
         * Dissalow construction from another instance; Singleton class
         */
        SystemController(SystemController const &) = delete;

        /**
         * Delete copy constructor; Singleton class
         */
        void operator=(SystemController const &) = delete;

        /**
         * Getter. Note that since this class is designed to be a singleton, only 1 instance will ever
         * exist in memory at any 1 time.
         */
        static SystemController &getSysCtrlInstance();

        /**
         *  This method initialises the system. It MUST be called before 'run' is executed.
         */
        bool init(Mode::ModeType initialMode);

        /**
         *  Check for whether system is initialised yet.
         */
        bool isInitialised() { return initialised; }

        /**
         *  This method should only ever be called forever from a permanent loop in main. This is the
         *  entry point to the normal flow of the program.
         */
        bool run();

        /**
         * Resets the system controller
         */
        void resetInstance();

        /**
         * Informs the controller that we should transition to the given mode next.
         */
        void shouldTransitionToMode(Mode::ModeType newMode);

        /**
         * Gets the currently active mode
         */
        Mode::Mode *getCurrentlyActiveMode();

    private:
        /**
         *  Private constructor; Singleton class
         */
        SystemController();

        /**
         * Makes the transition to the next mode
         */
        bool transitionToNextMode();

        /**
         * Testing
         */
#ifdef UNIT_TEST
        int test_value = 0;

    public:
        int getTestValue() { return test_value; }
        void setTestValue(int val) { test_value = val; }
#endif
    };
} // namespace Core

#endif /* CORE_SYSTEM_CONTROLLER_HPP */