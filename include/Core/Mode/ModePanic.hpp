#ifndef CORE_MODE_MODE_PANIC_HPP
#define CORE_MODE_MODE_PANIC_HPP

#include "Mode.hpp"

namespace Core {
    namespace Mode {
        class ModePanic : public Mode {
            public:
                void setup() override {
                }

                enum MODE_ID tick() override {
                    return MODE_ID::MODE_ID_FINALISE;
                }

                void teardown() override {
                }

                statemask get_statemask() const override {
                    return MODE_STATEMASK_PANIC;
                }
        };
    }
}

#endif /* CORE_MODE_MODE_PANIC_HPP */