#ifndef CORE_MODE_MODE_ACCEL_HPP
#define CORE_MODE_MODE_ACCEL_HPP

#include "Mode.hpp"

namespace Core {
    namespace Mode {
        class ModeAccel : public Mode {
            public:
                void setup() override {
                }

                enum MODE_ID tick() override {
                    return MODE_ID::MODE_ID_ACCEL;
                }

                void teardown() override {
                }

                statemask get_statemask() const override {
                    return MODE_STATEMASK_ACCEL;
                }
        };
    }
}

#endif /* CORE_MODE_MODE_ACCEL_HPP */