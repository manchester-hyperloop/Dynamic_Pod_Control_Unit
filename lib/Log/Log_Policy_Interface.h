//
//  Log_Policy_Interface.h
//  Logger
//
//  Created by Harry O'Brien on 17/10/2020.
//

#ifndef LIB_LOG_LOG_POLICY_INTERFACE_H
#define LIB_LOG_LOG_POLICY_INTERFACE_H

#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include "../../mocks/Arduino/Fake_Duino.hpp"
#endif

struct log_policy_interface
{
	virtual void open_ostream(const String &name) = 0;
	virtual void close_ostream() = 0;
	virtual void write(const String &msg) = 0;

	virtual ~log_policy_interface() {}
};

#endif /* LIB_LOG_LOG_POLICY_INTERFACE_H */
