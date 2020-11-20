//
//  Log_Policy.cpp
//  Logger
//
//  Created by Harry O'Brien on 17/10/2020.
//

#include "Log_Policy.h"

bool file_log_policy::open_ostream(const String &file_name)
{
    if (!sd.begin(CS_Pin))
    {
        Serial.println(F("LOGGER: Unable to initialise SD card..."));
        return false;
    }

    String dir_name = "Logs";
    sd.mkdir(dir_name.c_str());

    String const logPath = dir_name + "/" + "12345678.log"; //file_name;

    log_file = sd.open(logPath, FILE_WRITE);
    if (!log_file)
    {
        Serial.println(F("Logger: Unable to open an output stream!"));
        return false;
    }

    return true;
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
    log_file.println(msg);
#ifdef LOG_TO_SERIAL
    Serial.println(msg);
#endif
    log_file.flush();
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