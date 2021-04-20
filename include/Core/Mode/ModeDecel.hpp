#ifndef CORE_MODE_MODE_DECEL_HPP
#define CORE_MODE_MODE_DECEL_HPP

#include "Mode.hpp"

namespace Core {
    namespace Mode {
        class ModeDecel : public Mode {
            public:
                void setup() override {
                }

                enum MODE_ID tick() override {
                    return MODE_ID::MODE_ID_DECEL;
                }

                void teardown() override {
                }

                statemask get_statemask() const override {
                    return MODE_STATEMASK_DECEL;
                }
        };
    }
}

#endif /* CORE_MODE_MODE_DECEL_HPP */