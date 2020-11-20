//
//  Log.cpp
//  Logger
//
//  Created by Harry O'Brien on 19/10/2020.
//

#include "Log.hpp"

logger<file_log_policy> &log_inst = logger<file_log_policy>::getLoggerInstance();