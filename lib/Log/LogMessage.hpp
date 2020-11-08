#ifndef LIB_LOG_LOG_MESSAGE_HPP
#define LIB_LOG_LOG_MESSAGE_HPP

#ifndef UNIT_TEST

#include <avr/pgmspace.h>

#define TEST_LOG_MSG_1 0
#define TEST_LOG_MSG_2 1
#define TEST_LOG_MSG_3 2
#define TEST_LOG_MSG_4 3
#define TEST_LOG_MSG_5 4
#define TEST_LOG_MSG_6 5

const char string_0[] PROGMEM = "String 0"; // "String 0" etc are strings to store - change to suit.
const char string_1[] PROGMEM = "String 1";
const char string_2[] PROGMEM = "String 2";
const char string_3[] PROGMEM = "String 3";
const char string_4[] PROGMEM = "String 4";
const char string_5[] PROGMEM = "String 5";

const char *logMessage[] PROGMEM = {
    "Test log message!",
};

#endif /* UNIT_TEST */
#endif /* LOG_LOG_MESSAGE_HPP */