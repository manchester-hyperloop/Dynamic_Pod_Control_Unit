#ifndef CORE_MODE_MODE_STEADY_HPP
#define CORE_MODE_MODE_STEADY_HPP

#include "Mode.hpp"

namespace Core {
    namespace Mode {
        struct ModeSteady : public Mode {
                void setup(SystemController *state) override {
                }

                enum MODE_ID tick(SystemController *state) override {
                    return MODE_ID::MODE_ID_STEADY;
                }

                void teardown(SystemController *state) override {
                }

                statemask_t get_statemask() const override {
                    return MODE_STATEMASK_STEADY;
                }
        };
    }
}

#endif /* CORE_MODE_MODE_STEADY_HPP */