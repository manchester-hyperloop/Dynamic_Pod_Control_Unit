//
//  ModeShutdown.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 23/11/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef Core_Mode_Mode_Shutdown_Hpp
#define Core_Mode_Mode_Shutdown_Hpp

#include "Mode.hpp"
#include "ModeType.hpp"

namespace Core
{
    namespace Mode
    {
        class ModeShutdown : public Mode
        {
        public:
            ModeShutdown(SystemController *sysCtrl) : Mode(sysCtrl)
            {
            }

            ~ModeShutdown()
            {
            }

            /**
             * Initialise this mode
             */
            bool init() override
            {
                // Stop things moving
                // ...

                // Apply brakes
                // ...

                // Apply emergency-brakes
                // ...

                // Turn off power to pod (Exluding self and ODroid)
                // ...

                // Issue shutdown command to ODroid
                // ...

                // Turn off power to ODroid
                // ...

                return true;
            }

            /**
             * Executes the behaviour for this mode. Repeatedly called by SystemController.
             * If something fails part way through, the method will return false.
             */
            bool run() override
            {
                // This method shouldn't be called; we've shutdown
                return false;
            }

            /**
             * Gets the type of the mode
             */
            ModeType type() override
            {
                return ModeType::SHUTDOWN;
            }
        };

    } // namespace Mode

} // namespace Core

#endif /* Core_Mode_Mode_Shutdown_Hpp */