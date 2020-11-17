#ifndef CORE_PID_HPP
#define CORE_PID_HPP

// allows us to quickly switch the precision of the pid
typedef double __pid_value_t;

// allows us to quickly switch the backing time container type
typedef unsigned long __pid_time_t;

namespace Core {
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
        double next(const __pid_value_t source, const __pid_time_t current_time_us)
        {
            // calculate a dt between measurements
            const __pid_value_t dt = (__pid_value_t)(current_time_us - m_last_measured_us) / 1000000.0;

            // calculate new error between source value and target value
            const __pid_value_t error = m_setpoint - source;

            // update integral error
            m_error_sum += error * dt;

            // get the gradient between the last 2 error values, for the derivative error
            const __pid_value_t gradient = (error - m_last_error) / dt;

            // assigns temporary variables
            const __pid_value_t proportional = (m_kp * PARAM_SCALE) * error;
            const __pid_value_t integral = (m_ki * PARAM_SCALE) * m_error_sum;
            const __pid_value_t derivative = (m_kd * PARAM_SCALE) * gradient;

            // update last measurement time and last measured error
            m_last_error = error;
            m_last_measured_us = current_time_us;

            return proportional + integral + derivative;
        }

        const double getKp() { return m_kp; }
        const double getKi() { return m_ki; }
        const double getKd() { return m_kd; }
        const double getSetpoint() { return m_setpoint; }

        void setKp(const double val) { m_kp = val; }
        void setKi(const double val) { m_ki = val; }
        void setKd(const double val) { m_kd = val; }
        void setSetpoint(const double val) { m_setpoint = val; }
    };
}

#endif /* CORE_PID_HPP */