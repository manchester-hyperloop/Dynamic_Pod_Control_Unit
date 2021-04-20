#ifndef CORE_MODE_MODE_IDLE_HPP
#define CORE_MODE_MODE_IDLE_HPP

#include "Mode.hpp"

namespace Core {
    namespace Mode {
        class ModeIdle : public Mode {
            public:
                void setup() override {
                }

                enum MODE_ID tick() override {
                    return MODE_ID::MODE_ID_IDLE;
                }

                void teardown() override {
                }

                statemask get_statemask() const override {
                    return MODE_STATEMASK_IDLE;
                }
        };
    }
}

#endif /* CORE_MODE_MODE_IDLE_HPP */