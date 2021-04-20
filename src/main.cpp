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

#include <Log.hpp>

#include "Common/Wiring_Config.hpp"
#include "Core/SystemController.hpp"

volatile bool have_can_frame = false;
void can_isr();

void setup()
{
  // Start the serial port
  Serial.begin(115200);

  // Initialise the logger
  log_inst.init();

  // TODO: the arduino mock lacks this definition, so we get test failures
#ifndef UNIT_TEST
  attachInterrupt(digitalPinToInterrupt(HYPER_PIN_CAN_IRQ), can_isr, FALLING);
#endif
}

void loop()
{
  Core::SystemController &controller = Core::SystemController::getInstance();

  controller.init();

  controller.run();

  controller.finalise();

  while (1);
}

void can_isr() {
  have_can_frame = true;
}
