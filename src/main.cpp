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
#include "Core/Pid.hpp"
// #include "Core/Mode/"

Core::SystemController &ctrl = Core::SystemController::getSysCtrlInstance();
double pid_src = 0, pid_setpoint = 1.5, kp = 00, ki = 500, kd = 100;
Core::Pid pid = Core::Pid(pid_setpoint, kp, ki, kd);

void setup()
{
  Serial.begin(115200);
}

const unsigned long DELAY_TIME_US = 500000;
unsigned long last_delay_time_us = 0;

void loop()
{
  if ((micros() - last_delay_time_us) >= DELAY_TIME_US)
  {
    last_delay_time_us += DELAY_TIME_US;
    const double dt = last_delay_time_us / 1000000.0;

    Serial.print("Current time: ");
    Serial.print(dt);

    const double delta = pid.next(pid_src, last_delay_time_us);

    Serial.print(" | Src Value: ");
    Serial.print(pid_src);
    Serial.print(" | Tgt Value: ");
    Serial.print(pid_setpoint);
    Serial.print(" | Delta Value: ");
    Serial.print(delta);
    Serial.println();

    pid_src += delta;
  }
}

#endif /* ifndef UNIT_TEST */
