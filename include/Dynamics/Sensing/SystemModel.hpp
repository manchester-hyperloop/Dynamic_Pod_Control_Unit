//
//  SystemModel.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 11/11/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#include "../State.hpp"

namespace Dynamics
{
    namespace Sensing
    {
        class SystemModel
        {
        public:
            State getState()
            {
                return State();
            }
        };
    } // namespace Sensing

} // namespace Dynamics
