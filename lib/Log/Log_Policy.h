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

public:
	file_log_policy() {}
	void open_ostream(const String &file_name);
	void close_ostream();
	void write(const String &msg);
	~file_log_policy();

	SdFat &getFileSystem();
	File &getLogFile();
};

#endif /* LIB_LOG_LOG_POLICY_H */
