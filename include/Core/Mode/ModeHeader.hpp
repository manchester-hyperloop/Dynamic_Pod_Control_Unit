//
//  ModeHeader.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#include "Mode.hpp"
#include "ModeIdle.hpp"
#include "ModeAccel.hpp"
#include "ModeSteady.hpp"
#include "ModeDecel.hpp"
#include "ModePanic.hpp"

#ifdef UNIT_TEST
#include <Mode_Mock.hpp>
#endif
