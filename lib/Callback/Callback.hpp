//
//  main.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 8/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef LIB_CALLBACK_CALLBACK_HPP
#define LIB_CALLBACK_CALLBACK_HPP

/**
 * A structure for storing and handling pointers to callbacks, regardless of whether they are
 * methods or C style functions.
 */
template <typename T>
struct Callback
{
    virtual ~Callback() {}
    virtual void run(T) = 0;
};

// Specialised Callbacks (for cases where we have no params)
template <>
struct Callback<void>
{
    virtual ~Callback() {}
    virtual void run() = 0;
};

/**
 * A storage unit for a callback to a function, disconnected from any class. Note that the paramater 'T' can be of type 'void'
 */
template <typename T>
struct FuncCallback : public Callback<T>
{
    FuncCallback(void (*_function)(T)) : function(_function)
    {
    }

    void run(T param) override
    {
        if (function == nullptr)
            return;

        // Execute the callback
        (*function)(param);
    }

private:
    void (*function)(T);
};

// Specialised for 'void'
template <>
struct FuncCallback<void> : public Callback<void>
{
    FuncCallback(void (*_function)(void)) : function(_function)
    {
    }

    void run() override
    {
        if (function == nullptr)
            return;

        // Execute the function
        (*function)();
    }

private:
    void (*function)(void);
};

/**
 * A storage unit for a callback to a class method. Note that the parameter 'T' can be of type 'void'
 */
template <typename C, typename T>
struct MethodCallback : public Callback<T>
{
    MethodCallback(void (C::*_method)(T), C *_instance) : method(_method),
                                                          instance(_instance)
    {
    }

    void run(T param) override
    {
        if (method == nullptr || instance == nullptr)
            return;

        // Execute the method
        (instance->*method)(param);
    }

private:
    void (C::*method)(T);
    C *instance;
};

// Specialised for 'void'
template <typename C>
struct MethodCallback<C, void> : public Callback<void>
{
    MethodCallback(void (C::*_method)(void), C *_instance) : method(_method),
                                                             instance(_instance)
    {
    }

    void run() override
    {
        if (method == nullptr || instance == nullptr)
            return;

        (instance->*method)();
    }

private:
    void (C::*method)(void);
    C *instance;
};

#endif /* LIB_CALLBACK_CALLBACK_HPP */
