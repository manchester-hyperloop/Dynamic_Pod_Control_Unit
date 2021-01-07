//
//  Mode.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef CORE_MODE_MODE_HPP
#define CORE_MODE_MODE_HPP

#include "ModeType.hpp"

namespace Core
{
    class SystemController;

    namespace Mode
    {
        /**
         * Pure virtual class to define the behaviour of the system. Inhereted into other
         * modes, such as 'initialise', 'run' etc., which perform tasks relevant to their
         * name.
         */
        class Mode
        {
        protected:
            SystemController *sysCtrl;

        public:
            Mode(SystemController *_sysCtrl) : sysCtrl(_sysCtrl)
            {
            }

            virtual ~Mode()
            {
            }

            /**
             * Initialise this mode
             */
            virtual bool init() = 0;

            /**
             * Executes the behaviour for this mode. Repeatedly called by SystemController.
             * If something fails part way through, the method will return false.
             */
            virtual bool run() = 0;

            /**
             * Gets the type of the mode
             */
            virtual ModeType type() = 0;
        };
    } // namespace Mode
} // namespace Core

#endif /* CORE_MODE_MODE_HPP */
