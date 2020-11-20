//
//  Log.hpp
//  Logger
//
//  Created by Harry O'Brien on 17/10/2020.
//

#ifndef LIB_LOG_LOG_HPP
#define LIB_LOG_LOG_HPP

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

    template <severity_type severity, typename... Args>
    void print(Args... args);

    unsigned int getLastMessageIndex() const;
    file_log_policy *getActiveLogPolicy() const;

private:
    logger();

    String get_time(bool dateAndTime = false) const;
    String get_logline_header() const;

    String generateLogName();

    //Core printing functionality
    void print_impl();

    template <typename First, typename... Rest>
    void print_impl(First parm1, Rest... parm);
};

template <typename log_policy>
logger<log_policy>::logger()
{
    if (!rtc.begin())
    {
        // TODO: Create critical error!
        Serial.println("Couldn't find RTC...");
    }

    String name = generateLogName();
    policy = new log_policy;
    if (!policy)
    {
        // TODO: Create critical error!
        Serial.println(F("LOGGER: Unable to create the logger instance"));
    }
    policy->open_ostream(name);
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

// TODO: Implement with RTC
template <typename log_policy>
String logger<log_policy>::get_time(bool dateAndTime) const
{
    DateTime time = rtc.now();
    if (dateAndTime)
        return time.timestamp(DateTime::TIMESTAMP_FULL);
    else
        return time.timestamp(DateTime::TIMESTAMP_TIME);
}

template <typename log_policy>
String logger<log_policy>::get_logline_header() const
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
    time = time.replace(':', '.');
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

static logger<file_log_policy> &log_inst = logger<file_log_policy>::getLoggerInstance();

#ifdef LOGGING_LEVEL_1
#define LOG log_inst.print<severity_type::debug>
#define LOG_ERR log_inst.print<severity_type::error>
#define LOG_WARN log_inst.print<severity_type::warning>
#else
#define LOG(...)
#define LOG_ERR(...)
#define LOG_WARN(...)
#endif

#ifdef LOGGING_LEVEL_2
#define ELOG log_inst.print<severity_type::debug>
#define ELOG_ERR log_inst.print<severity_type::error>
#define ELOG_WARN log_inst.print<severity_type::warning>
#else
#define ELOG(...)
#define ELOG_ERR(...)
#define ELOG_WARN(...)
#endif

#endif /* LIB_LOG_LOG_HPP */
