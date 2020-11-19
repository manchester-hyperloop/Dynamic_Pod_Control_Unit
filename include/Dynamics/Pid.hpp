#ifndef DYNAMICS_PID_HPP
#define DYNAMICS_PID_HPP

// allows us to quickly switch the precision of the pid
typedef double __pid_value_t;

// allows us to quickly switch the backing time container type
typedef unsigned long __pid_time_t;

namespace Dynamics {
    /// Proportional-Integral-Derivative controller, used to converge to a set value over time.
    class Pid {
    private:
        __pid_value_t m_setpoint; // target value
        __pid_value_t m_kp, m_ki, m_kd; // tuning parameters
        __pid_value_t m_error_sum; // used to calculate the integral error
        __pid_value_t m_last_error; // used to calculate the derivative error
        __pid_time_t m_last_measured_us; // the last time a measurement was made

        // scaling factor to leave pid params in 1000s
        static constexpr __pid_value_t PARAM_SCALE = 0.001;

    public:
        /// Initialises a new instance of the Pid class.
        /// @param setpoint The target value which we want to reach
        /// @param kp The proportional error tuning parameter. How hard we work to correct error
        /// @param ki The integral error tuning parameter. How much we counteract drift in the measured value
        /// @param kd The derivative error tuning parameter. How much we dampen overcorrection
        Pid(const __pid_value_t setpoint, const __pid_value_t kp, const __pid_value_t ki, const __pid_value_t kd)
            : m_setpoint(setpoint), m_kp(kp), m_ki(ki), m_kd(kd)
        {
            m_error_sum = 0;
            m_last_error = 0;
            m_last_measured_us = 0;
        }

        /// Calculates the next target value.
        /// @param source The current measured value
        /// @param current_time_us The current time. Must be > 0 and must only increase
        /// @returns The target value necessary to reach the setpoint
        /// @remark Adapted from https://en.wikipedia.org/wiki/PID_controller#Controller_theory
        __pid_value_t next(const __pid_value_t source, const __pid_time_t current_time_us);

        const __pid_value_t getKp() { return m_kp; }
        const __pid_value_t getKi() { return m_ki; }
        const __pid_value_t getKd() { return m_kd; }
        const __pid_value_t getSetpoint() { return m_setpoint; }

        void setKp(const __pid_value_t val) { m_kp = val; }
        void setKi(const __pid_value_t val) { m_ki = val; }
        void setKd(const __pid_value_t val) { m_kd = val; }
        void setSetpoint(const __pid_value_t val) { m_setpoint = val; }
    };
}

#endif /* DYNAMICS_PID_HPP */