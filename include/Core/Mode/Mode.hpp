//
//  Mode.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef CORE_MODE_MODE_HPP
#define CORE_MODE_MODE_HPP

typedef uint8_t statemask;

namespace Core
{
    class SystemController;

    namespace Mode
    {
        enum MODE_ID {
            MODE_ID_FINALISE = 0xff, // special value to signify shutdown
            MODE_ID_IDLE = 0,
            MODE_ID_ACCEL = 1,
            MODE_ID_STEADY = 2,
            MODE_ID_DECEL = 3,
            MODE_ID_PANIC = 4,
        };

        /// Mode interface
        class Mode
        {
        protected:
            SystemController *sysCtrl;

        public:
            static constexpr statemask MODE_STATEMASK_DEFAULT = 0xff;
            static constexpr statemask MODE_STATEMASK_NULL = 0x00;
            static constexpr statemask MODE_STATEMASK_IDLE = 0x01;
            static constexpr statemask MODE_STATEMASK_ACCEL = 0x02;
            static constexpr statemask MODE_STATEMASK_STEADY = 0x04;
            static constexpr statemask MODE_STATEMASK_DECEL = 0x08;
            static constexpr statemask MODE_STATEMASK_PANIC = 0x10;

            Mode(SystemController *_sysCtrl) : sysCtrl(_sysCtrl)
            {
            }

            /// Called whenever control is to be handed to the mode
            virtual void setup() = 0;

            /// The "main loop" body
            /// @returns The id of the mode to hand control to
            virtual enum MODE_ID tick() = 0;

            /// Called whenever control is to be taken from the mode
            virtual void teardown() = 0;

            /// Statemask used to calculate which event handlers should be ran
            /// @returns The satemask for the current state
            virtual statemask get_statemask() const = 0;
        };
    }
}

#endif /* CORE_MODE_MODE_HPP */
