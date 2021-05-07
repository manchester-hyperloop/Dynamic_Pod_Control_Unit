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
#include <Arduino_Mock.hpp>
#endif

// #include "Core/SystemController.hpp"
#include <Log.hpp>

// Core::SystemController &ctrl = Core::SystemController::getSysCtrlInstance();

void setup()
{
  // Start the serial port
  Serial.begin(115200);

  // Initialise the logger
  log_inst.init();
  //LOG("Starting...");

  // ctrl.init(nullptr);
}

void loop()
{
  LOG_ERR("Error_Test");
  LOG_WARN("Warning_Test");
}
