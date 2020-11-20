//
//  main.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 8/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include "../../mocks/Arduino/Fake_Duino.hpp"
#endif

#include "Core/SystemController.hpp"
#include <Log.hpp>

Core::SystemController &ctrl = Core::SystemController::getSysCtrlInstance();

void setup()
{
  Serial.begin(115200);
  LOG("Starting...");

  ctrl.init(nullptr);
}

void loop()
{
}
