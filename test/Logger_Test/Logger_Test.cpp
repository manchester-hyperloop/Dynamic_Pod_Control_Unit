//
//  Logger_Test.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#include <unity.h>
#include <Log.hpp>
#include <string>
#include <sstream>
#include <iostream>

#include "../../mocks/sd_mocks/SdFat.h"
#include "../../mocks/rtc_mocks/RTC_Lib_Mock.hpp"
#include "../../mocks/Arduino/Fake_Duino.hpp"

logger<file_log_policy> &test_log_inst = logger<file_log_policy>::getLoggerInstance();

// Helper
file_log_policy *getActiveLogPolicy()
{
    file_log_policy *policy = test_log_inst.getActiveLogPolicy();
    TEST_ASSERT(policy != nullptr);

    return policy;
}

void test_message_index_starts_at_0(void)
{
    // Initially, index should be -1 (no messages have been logged yet!)
    TEST_ASSERT(test_log_inst.getLastMessageIndex() == -1);

    // Log a message
    LOG("Testing 123");

    // Last index written should now be 0
    TEST_ASSERT(test_log_inst.getLastMessageIndex() == 0);
}

// logger should print index of each log message
void test_log_message_index(void)
{
    // Get last index written
    unsigned long const lastIndex = test_log_inst.getLastMessageIndex();

    // Log a message
    LOG("Testing 123");

    // Index should now be 1 more than previous
    TEST_ASSERT(test_log_inst.getLastMessageIndex() == lastIndex + 1);

    // Get the mock sd instance;
    file_log_policy *policy = getActiveLogPolicy();

    // get the log file and check if the last message = this message
    File log_file_mock = policy->getLogFile();

    TEST_ASSERT(log_file_mock.lastMessage[0] == '1');
}

// logger should save the message passed to it to SD
void test_logger_should_save_message_to_sd(void)
{
    // Log a message
    // DO NOT RE-USE OR CHANGE THIS MESSAGE; IT IS UNIQUE HERE!
    std::string message = "test_logger_should_save_message_to_sd";
    LOG(message);

    // Get the mock sd instance;
    file_log_policy *policy = getActiveLogPolicy();

    // get the log file and check if the last message = this message
    File log_file_mock = policy->getLogFile();

    TEST_ASSERT(log_file_mock.lastMessage.find(message));
}

// logger should be able to take variadic arguments of different types and print all of them
void test_logger_takes_variadic_args(void)
{
    std::string const message1 = "my testy boi val is: ";
    unsigned int test_val = 2334;
    std::string const message2 = " and some bool is: ";
    bool test_bool = false;

    LOG(message1, test_val, message2, test_bool);

    // Get the mock sd instance;
    file_log_policy *policy = getActiveLogPolicy();

    // get the log file and check if the last message = this message
    File log_file_mock = policy->getLogFile();

    std::string compiledMessage = message1 + patch::to_string(test_val) + message2 + patch::to_string(test_bool);

    TEST_ASSERT(log_file_mock.lastMessage.find(compiledMessage) != -1);
}

// logger should print time with each message
void test_logger_prints_time(void)
{
    // Log a message
    // DO NOT RE-USE OR CHANGE THIS MESSAGE; IT IS UNIQUE HERE!
    LOG("test_logger_prints_time");

    // Get the mock sd instance;
    file_log_policy *policy = getActiveLogPolicy();

    // get the log file and check if the last message contains time
    File log_file_mock = policy->getLogFile();

    // Get the 'time'
    RTC_DS1307 rtc_mock;
    std::string timeNow = rtc_mock.now().timestamp(DateTime::timestampOpt::TIMESTAMP_TIME);

    TEST_ASSERT(log_file_mock.lastMessage.find(timeNow) != -1);
}

// logger should print either, INFO, ERROR, or WARNING with each message depending on severity
void test_logger_prints_severity(void)
{
    // Get the mock sd instance;
    file_log_policy *policy = getActiveLogPolicy();

    // get the log file and check if the last message contains time
    File log_file_mock = policy->getLogFile();

    // test for debug
    LOG("test_logger_prints_severity (debug)");
    TEST_ASSERT(log_file_mock.lastMessage.find("DEBUG") != -1);

    LOG_WARN("test_logger_prints_severity (warn)");
    TEST_ASSERT(log_file_mock.lastMessage.find("WARNING") != -1);

    LOG_ERR("test_logger_prints_severity (err)");
    TEST_ASSERT(log_file_mock.lastMessage.find("ERROR") != -1);
}

// Logger should fail to start and return false if unable to initialise SD card hardware
void test_logger_fails_on_sd_failure(void)
{
}

// Logger should fail to start and return false if unable to open an output stream
void test_logger_fails_on_output_failure(void)
{
}

// Logger should fail to start and return fals if unable to start real-time clock (RTC)
void test_logger_fails_on_rtc_failure(void)
{
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_message_index_starts_at_0);
    RUN_TEST(test_log_message_index);
    RUN_TEST(test_logger_should_save_message_to_sd);
    RUN_TEST(test_logger_takes_variadic_args);
    RUN_TEST(test_logger_prints_time);
    RUN_TEST(test_logger_prints_severity);
    RUN_TEST(test_logger_fails_on_sd_failure);
    RUN_TEST(test_logger_fails_on_output_failure);
    RUN_TEST(test_logger_fails_on_rtc_failure);

    UNITY_END();
}