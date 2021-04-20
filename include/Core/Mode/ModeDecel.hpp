#ifndef CORE_MODE_MODE_DECEL_HPP
#define CORE_MODE_MODE_DECEL_HPP

#include "Mode.hpp"

namespace Core {
    namespace Mode {
        struct ModeDecel : public Mode {
                void setup(SystemController *state) override {
                }

                enum MODE_ID tick(SystemController *state) override {
                    return MODE_ID::MODE_ID_DECEL;
                }

                void teardown(SystemController *state) override {
                }

                statemask_t get_statemask() const override {
                    return MODE_STATEMASK_DECEL;
                }
        };
    }
}

#endif /* CORE_MODE_MODE_DECEL_HPP */