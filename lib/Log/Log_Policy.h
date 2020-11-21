//
//  Log_Policy.h
//  Logger
//
//  Created by Harry O'Brien on 17/10/2020.
//

#ifndef LIB_LOG_LOG_POLICY_H
#define LIB_LOG_LOG_POLICY_H

#include "Log_Policy_Interface.h"

#ifndef UNIT_TEST
#include <Arduino.h>
#include <SdFat.h>
#else
#include "../../mocks/Arduino/Fake_Duino.hpp"
#include "../../mocks/sd_mocks/SdFat.h"
#endif

/*
 * Implementation which allow to write into a file
 */

class file_log_policy : public log_policy_interface
{
	// File system object.
	SdFat sd;

	// Log file.
	File log_file;

	// CS Pin
	uint8_t const CS_Pin = 10;

public:
	file_log_policy() {}
	bool open_ostream(const String &file_name) override;
	void close_ostream() override;
	void write(const String &msg) override;
	~file_log_policy();

	File &getLogFile();
};

#endif /* LIB_LOG_LOG_POLICY_H */
