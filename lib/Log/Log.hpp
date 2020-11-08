//
//  Log.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef LIB_LOG_LOG_HPP
#define LIB_LOG_LOG_HPP

class Log
{
    char *const logLocation = "./logs/";
    char *fileName = nullptr;

public:
    void init();

#ifdef UNIT_TEST
    // Set log file name
    void init(char *fileName);
#endif

    static Log &getInstance();

    void operator()(const char *message, int parameter, const char *fileName, int line);

    void resetInstance();

private:
    Log();

    void setFileName(char *newName);
};

#define LOG(description, parameter) \
    Log::getInstance()(description, parameter, __FILE__, __LINE__);

#endif /* LIB_LOG_LOG_HPP */