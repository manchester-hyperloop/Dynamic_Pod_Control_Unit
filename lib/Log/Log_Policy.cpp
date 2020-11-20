//
//  Log_Policy.cpp
//  Logger
//
//  Created by Harry O'Brien on 17/10/2020.
//

#include "Log_Policy.h"

// TODO: Return boolean
void file_log_policy::open_ostream(const String &file_name)
{
    if (!sd.begin(10))
    {
        // TODO: Create critical error!
        Serial.println(F("LOGGER: Unable to initialise SD card..."));
        return;
    }

    String dir_name = "Logs";
    sd.mkdir(dir_name.c_str());
    String const logPath = dir_name + "/" + file_name;

    log_file = sd.open(logPath, FILE_WRITE);
    if (!log_file)
    {
        // TODO: Create critical error!
        Serial.println(F("Logger: Unable to open an output stream!"));
        return;
    }
}

void file_log_policy::close_ostream()
{
    if (log_file)
    {
        log_file.close();
    }
}

void file_log_policy::write(const String &msg)
{
    log_file.print(msg);
#ifdef LOG_TO_SERIAL
    Serial.println(msg);
#endif
}

file_log_policy::~file_log_policy()
{
    if (log_file)
    {
        close_ostream();
    }
}

SdFat &file_log_policy::getFileSystem()
{
    return sd;
}

File &file_log_policy::getLogFile()
{
    return log_file;
}