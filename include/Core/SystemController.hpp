//
//  SystemController.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef CORE_SYSTEM_CONTROLLER_HPP
#define CORE_SYSTEM_CONTROLLER_HPP

#include <Log.hpp>

// TODO(mikolaj): this define is here because include paths on my computer are 
// a bit screwed, and it cannot find the can interface header. once i get that
// fixed, both it and the related HAS_CAN_BUS define can be removed
//#define HAS_CAN_BUS

#ifdef HAS_CAN_BUS
#include <CAN_Interface.hpp>
#endif

#include "Mode/Mode.hpp"

// TODO: Initialise timestamp on first load
// Probs best to do this with onboard EEPROM

namespace Core
{
    class SystemController
    {
        bool initialised = false;

        Mode::MODE_ID previousMode, currentMode;

#ifdef HAS_CAN_BUS
        CAN_Interface can_bus;
#endif

    public:
        /// Disallow construction from another instance as we are a singleton
        SystemController(SystemController const &) = delete;

        /// Delete copy constructor as we are a singleton
        void operator=(SystemController const &) = delete;

        /// Singleton instance getter
        /// @returns The singleton instance of the system controller
        static SystemController &getInstance();

        /// This method initialises the system. MUST be called before 'run' is executed
        /// @param initialMode The state we should start in
        /// @returns Whether the initialisation was successful
        bool init(const Mode::MODE_ID initialState = Mode::MODE_ID_IDLE);

        /// Whether the system controller instance has been successfully initialised
        bool isInitialised() const { return initialised; }

        /// This method deinitialises the system
        void finalise();

        /// Entrypoint into the state machine. Blocks until a state signals a
        /// transition into the finalised state. MUST NOT be called after 'finalise' is executed
        /// @returns Whether the state machine exited gracefully (i.e didn't panic)
        bool run();

        /// Resets the system controller instance. MUST NOT be called after 'finalise' is executed
        void reset();

        /// Previous mode getter
        /// @returns A read-only pointer to the previously active mode
        const Mode::Mode *getPreviousMode() const;

        /// Active mode getter
        /// @returns A read-only pointer to the currently active mode
        const Mode::Mode *getCurrentMode() const;

        /// Generic mode getter. Allows indexing to find any given mode
        /// @returns A read-only pointer to the mode with the given id
        const Mode::Mode *getModeById(const Mode::MODE_ID id) const;

    private:
        /// Singleton instance constructor
        SystemController();

#ifdef UNIT_TEST
        int test_value = 0;

    public:
        int getTestValue() { return test_value; }
        void setTestValue(int val) { test_value = val; }
#endif
    };
}

#endif /* CORE_SYSTEM_CONTROLLER_HPP */