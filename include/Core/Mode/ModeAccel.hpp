#ifndef CORE_MODE_MODE_ACCEL_HPP
#define CORE_MODE_MODE_ACCEL_HPP

#include "Mode.hpp"

namespace Core {
    namespace Mode {
        struct ModeAccel : public Mode {
                void setup(SystemController *state) override {
                }

                enum MODE_ID tick(SystemController *state) override {
                    return MODE_ID::MODE_ID_ACCEL;
                }

                void teardown(SystemController *state) override {
                }

                statemask_t get_statemask() const override {
                    return MODE_STATEMASK_ACCEL;
                }
        };
    }
}

#endif /* CORE_MODE_MODE_ACCEL_HPP */