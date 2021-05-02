#ifndef CORE_MODE_MODE_IDLE_HPP
#define CORE_MODE_MODE_IDLE_HPP

#include "Mode.hpp"

namespace Core {
    namespace Mode {
        struct ModeIdle : public Mode {
                void setup(SystemController *state) override {
                }

                enum MODE_ID tick(SystemController *state) override {
                    return MODE_ID::MODE_ID_IDLE;
                }

                void teardown(SystemController *state) override {
                }

                statemask_t get_statemask() const override {
                    return MODE_STATEMASK_IDLE;
                }
        };
    }
}

#endif /* CORE_MODE_MODE_IDLE_HPP */