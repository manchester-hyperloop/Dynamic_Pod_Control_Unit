//
//  Mode.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef CORE_MODE_MODE_HPP
#define CORE_MODE_MODE_HPP

#include <stdint.h>

typedef uint8_t statemask_t;

namespace Core
{
    class SystemController;

    namespace Mode
    {
        /// Uniquely identifies each mode. Used as an index into a states table
        enum MODE_ID {
            MODE_FINALISE = 0xff, // special value to signify shutdown
            MODE_ID_IDLE = 0,
            MODE_ID_ACCEL = 1,
            MODE_ID_STEADY = 2,
            MODE_ID_DECEL = 3,
            MODE_ID_PANIC = 4,
#ifdef UNIT_TEST
            MODE_ID_TEST = 5,
#endif
        };

#ifdef UNIT_TEST
        constexpr size_t MODE_COUNT = 6;
#else
        constexpr size_t MODE_COUNT = 5;
#endif

        /// Mode interface
        struct Mode
        {
            static constexpr statemask_t MODE_STATEMASK_DEFAULT = 0xff;
            static constexpr statemask_t MODE_STATEMASK_NULL = 0x00;
            static constexpr statemask_t MODE_STATEMASK_IDLE = 0x01;
            static constexpr statemask_t MODE_STATEMASK_ACCEL = 0x02;
            static constexpr statemask_t MODE_STATEMASK_STEADY = 0x04;
            static constexpr statemask_t MODE_STATEMASK_DECEL = 0x08;
            static constexpr statemask_t MODE_STATEMASK_PANIC = 0x10;
#ifdef UNIT_TEST
            static constexpr statemask_t MODE_STATEMASK_TEST = 0x80;
#endif

            /// Called whenever control is to be handed to the mode
            virtual void setup(SystemController *state) = 0;

            /// The "main loop" body
            /// @returns The id of the mode to hand control to
            virtual MODE_ID tick(SystemController *state) = 0;

            /// Called whenever control is to be taken from the mode
            virtual void teardown(SystemController *state) = 0;

            /// Statemask used to calculate which event handlers should be ran
            /// @returns The satemask for the current state
            virtual statemask_t get_statemask() const = 0;
        };
    }
}

#endif /* CORE_MODE_MODE_HPP */
