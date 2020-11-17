#ifndef CORE_PID_HPP
#define CORE_PID_HPP


// `__time_t` is shorter than `unsigned long`, and we dont use `uxxx_t` :(
typedef unsigned long __time_t;

namespace Core {
    /// Proportional-Integral-Derivative controller, used to converge to a set value over time.
    class Pid {
    private:
        double m_setpoint; // target value
        double m_kp, m_ki, m_kd; // tuning parameters
        double m_error_sum; // used to calculate the integral error
        double m_last_error; // used to calculate the derivative error
        __time_t m_last_measured_us; // the last time a measurement was made

        // scaling factor to leave pid params in 1000s
        static constexpr double __pid_param_scale = 0.001;

    public:
        /// Initialises a new instance of the Pid class.
        /// @param setpoint The target value which we want to reach
        /// @param kp The proportional error tuning parameter. How hard we work to correct error
        /// @param ki The integral error tuning parameter. How much we counteract drift in the measured value
        /// @param kd The derivative error tuning parameter. How much we dampen overcorrection
        Pid(const double setpoint, const double kp, const double ki, const double kd)
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
        double next(const double source, const __time_t current_time_us)
        {
            // calculate a dt between measurements
            const double dt = (double)(current_time_us - m_last_measured_us) / 1000000.0;

            // calculate new error between source value and target value
            const double error = m_setpoint - source;

            // update integral error
            m_error_sum += error * dt;

            // get the gradient between the last 2 error values, for the derivative error
            const double gradient = (error - m_last_error) / dt;

            // assigns temporary variables
            const double proportional = (m_kp * __pid_param_scale) * error;
            const double integral = (m_ki * __pid_param_scale) * m_error_sum;
            const double derivative = (m_kd * __pid_param_scale) * gradient;

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