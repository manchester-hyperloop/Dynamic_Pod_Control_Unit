#include "Dynamics/Pid.hpp"

using namespace Dynamics;

__pid_value_t Pid::next(const __pid_value_t source, const __pid_time_t current_time_us)
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