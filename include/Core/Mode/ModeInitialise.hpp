//
//  ModeInitialise.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 23/11/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef Core_Mode_Mode_Initialise_Hpp
#define Core_Mode_Mode_Initialise_Hpp

#include "Mode.hpp"
#include "ModeType.hpp"

namespace Core
{
    namespace Mode
    {
        class ModeInitialise : public Mode
        {
        public:
            ModeInitialise(SystemController *sysCtrl) : Mode(sysCtrl)
            {
            }

            ~ModeInitialise()
            {
            }

            /**
             * Initialise this mode
             */
            bool init() override
            {
                // Send stop command to motorsmoving
                // ...

                // Apply brakes
                // ...

                // Apply emergency-brakes
                // ...

                // Turn on power to entire pod
                // ...

                // Establish connection to ODroid
                // ...

                // Initialise sensors
                // ...

                return true;
            }

            /**
             * Executes the behaviour for this mode. Repeatedly called by SystemController.
             * If something fails part way through, the method will return false.
             */
            bool run() override
            {
                // Transition to Idle
                sysCtrl->shouldTransitionToMode(IDLE);

                return true;
            }

            /**
             * Gets the type of the mode
             */
            ModeType type() override
            {
                return ModeType::INITIALISE;
            }
        };

    } // namespace Mode

} // namespace Core

#endif /* Core_Mode_Mode_Initialise_Hpp */