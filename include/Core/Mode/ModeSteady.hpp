#ifndef CORE_MODE_MODE_STEADY_HPP
#define CORE_MODE_MODE_STEADY_HPP

#include "Mode.hpp"

namespace Core {
    namespace Mode {
        class ModeSteady : public Mode {
            public:
                void setup() override {
                }

                enum MODE_ID tick() override {
                    return MODE_ID::MODE_ID_STEADY;
                }

                void teardown() override {
                }

                statemask get_statemask() const override {
                    return MODE_STATEMASK_STEADY;
                }
        };
    }
}

#endif /* CORE_MODE_MODE_STEADY_HPP */