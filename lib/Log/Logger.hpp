//
//  Logger.hpp
//  Logger
//
//  Created by Harry O'Brien on 19/10/2020.
//

#ifndef LIB_LOG_LOGGER_HPP
#define LIB_LOG_LOGGER_HPP

#include "Severity_Type.h"
#include "Log_Policy.h"

#ifndef UNIT_TEST
#include <RTClib.h>
#include <Arduino.h>
#else
#include "../../mocks/rtc_mocks/RTC_Lib_Mock.hpp"
#include "../../mocks/Arduino/Fake_Duino.hpp"
#endif

template <typename log_policy>
class logger
{
    unsigned int log_line_number = -1;

    String log_stream = "";
    log_policy *policy = nullptr;

    RTC_DS1307 rtc;

    bool initialised = false;

public:
    /**
	 * Dissalow construction from another instance; Singleton class
	 */
    logger(logger const &) = delete;

    /**
	 * Delete copy constructor; Singleton class
	 */
    void operator=(logger const &) = delete;

    static logger &getLoggerInstance();
    ~logger();

    bool init();

    template <severity_type severity, typename... Args>
    void print(Args... args);

    unsigned int getLastMessageIndex() const;
    file_log_policy *getActiveLogPolicy() const;

    void reset()
    {
        Serial.println(F("WARNING: Resetting Logger!"));
        initialised = false;
        delete policy;
        policy = nullptr;
    }

private:
    logger() {}

    String get_time(bool dateAndTime);
    String get_logline_header();

    String generateLogName();

    //Core printing functionality
    void print_impl();

    template <typename First, typename... Rest>
    void print_impl(First parm1, Rest... parm);
};

template <typename log_policy>
bool logger<log_policy>::init()
{
    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC...");
        return false;
    }

    policy = new log_policy;

    // Check that policy was created successfully (not nullptr)
    if (!policy)
    {
        Serial.println(F("LOGGER: Unable to create the logger instance"));
        return false;
    }

    String name = generateLogName();
    initialised = policy->open_ostream(name);

    return initialised;
}

template <typename log_policy>
logger<log_policy> &logger<log_policy>::getLoggerInstance()
{
    static logger<log_policy> loggerInstance;
    return loggerInstance;
}

template <typename log_policy>
logger<log_policy>::~logger()
{
    if (policy)
    {
        policy->close_ostream();
        delete policy;
    }
}

template <typename log_policy>
template <severity_type severity, typename... Args>
void logger<log_policy>::print(Args... args)
{
    // Return if not initialised (prevents crash later when accessing policy)
    if (!initialised)
        return;

    switch (severity)
    {
    case severity_type::debug:
        log_stream += "<DEBUG>: ";
        break;
    case severity_type::warning:
        log_stream += "<WARNING>: ";
        break;
    case severity_type::error:
        log_stream += "<ERROR>: ";
        break;
    };

    print_impl(args...);
}

template <typename log_policy>
String logger<log_policy>::get_time(bool dateAndTime)
{
    DateTime time = rtc.now();
    if (dateAndTime)
        return time.timestamp(DateTime::TIMESTAMP_FULL);
    else
        return time.timestamp(DateTime::TIMESTAMP_TIME);
}

template <typename log_policy>
String logger<log_policy>::get_logline_header()
{
    String header = "";

    header += String(++log_line_number) + " < " + get_time(false) + " - ";

    header += String(micros()) + " > ~ ";

    return header;
}

template <typename log_policy>
String logger<log_policy>::generateLogName()
{
    String time = get_time(true);
#ifndef UNIT_TEST
    time.replace(':', '.');
#endif
    return time + ".log";
}

template <typename log_policy>
void logger<log_policy>::print_impl()
{
    policy->write(get_logline_header() + log_stream);
    log_stream = "";
}

template <typename log_policy>
template <typename First, typename... Rest>
void logger<log_policy>::print_impl(First parm1, Rest... parm)
{
    log_stream += String(parm1);
    print_impl(parm...);
}

template <typename log_policy>
unsigned int logger<log_policy>::getLastMessageIndex() const
{
    return log_line_number;
}

template <typename log_policy>
file_log_policy *logger<log_policy>::getActiveLogPolicy() const
{
    return policy;
}

#endif /* LIB_LOG_LOGGER_HPP */