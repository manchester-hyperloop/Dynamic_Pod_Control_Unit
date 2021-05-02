#ifndef CORE_MODE_MODE_PANIC_HPP
#define CORE_MODE_MODE_PANIC_HPP

#include "Mode.hpp"

namespace Core {
    namespace Mode {
        struct ModePanic : public Mode {
                void setup(SystemController *state) override {
                }

                enum MODE_ID tick(SystemController *state) override {
                    return MODE_ID::MODE_FINALISE;
                }

                void teardown(SystemController *state) override {
                }

                statemask_t get_statemask() const override {
                    return MODE_STATEMASK_PANIC;
                }
        };
    }
}

#endif /* CORE_MODE_MODE_PANIC_HPP */