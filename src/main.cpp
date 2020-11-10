//
//  main.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 8/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef UNIT_TEST
#include <Arduino.h>
#include "Core/SystemController.hpp"
// #include "Core/Mode/"

Core::SystemController &ctrl = Core::SystemController::getSysCtrlInstance();

void setup()
{
  Serial.begin(115200);
  ctrl.init(nullptr);
}

void loop()
{
}
#endif /* ifndef UNIT_TEST */
