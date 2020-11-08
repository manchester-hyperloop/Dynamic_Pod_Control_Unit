#ifndef LIB_LOG_ERROR_MESSAGE_HPP
#define LIB_LOG_ERROR_MESSAGE_HPP

#ifndef UNIT_TEST

#include <avr/pgmspace.h>

#define ERROR_TEST 0
#define ERROR_CRITICAL 1

const char *errorMessage[] PROGMEM = {
    "Test error message!",
    "A critical error has occurred.",
};

#endif /* UNIT_TEST */
#endif /* LIB_LOG_ERROR_MESSAGE_HPP */