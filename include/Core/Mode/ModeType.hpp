//
//  ModeType.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef CORE_MODE_MODE_TYPE_HPP
#define CORE_MODE_MODE_TYPE_HPP

namespace Core
{
    namespace Mode
    {
        enum ModeType
        {
            INITIALISE,
            IDLE,
            SHUTDOWN,

#ifdef UNIT_TEST
            TEST
#endif
        };

        /**
         * Functor 'ModeNameInverse' that is able to take a ModeType and return a human-readable version
         */
        struct
        {
            const char *operator()(ModeType e)
            {
                const char *ModeName[] = {
                    "Initialise",
                    "Idle",
                    "Shutdown",

                    "Test",
                };

                return ModeName[e];
            }
        } ModeNameInverse;
    } // namespace Mode
} // namespace Core

#endif /* CORE_MODE_MODE_TYPE_HPP */
