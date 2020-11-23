//
//  ModeIdle.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 23/11/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef Core_Mode_Mode_Idle_Hpp
#define Core_Mode_Mode_Idle_Hpp

#include "Mode.hpp"
#include "ModeType.hpp"

namespace Core
{
    namespace Mode
    {
        class ModeIdle : public Mode
        {
        public:
            ModeIdle(SystemController *sysCtrl) : Mode(sysCtrl)
            {
            }

            ~ModeIdle()
            {
            }

            /**
             * Initialise this mode
             */
            bool init() override
            {
                // stop everything moving
                // ...

                return true;
            }

            /**
             * Executes the behaviour for this mode. Repeatedly called by SystemController.
             * If something fails part way through, the method will return false.
             */
            bool run() override
            {
                Mode::run();

                // Do nothing; we're idling...
                return true;
            }

            /**
             * Gets the type of the mode
             */
            ModeType type() override
            {
                return ModeType::IDLE;
            }
        };

    } // namespace Mode

} // namespace Core

#endif /* Core_Mode_Mode_Idle_Hpp */