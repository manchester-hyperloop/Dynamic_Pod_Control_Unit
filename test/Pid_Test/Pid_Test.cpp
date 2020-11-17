#include <unity.h>
#include "Core/Pid.hpp"
#include <Instance.hpp>

void setup(void)
{
}

void tearDown(void)
{
}

void test_pid_works(void)
{
    double pid_src = 0, pid_setpoint = 1.5, kp = 500, ki = 500, kd = 100;
    Core::Pid pid = Core::Pid(pid_setpoint, kp, ki, kd);

    // if working it should approach value
    const size_t iters = 100;
    for (size_t i = 0; i < iters; i++)
    {
        const unsigned long time = (i + 1) * 1000000;
        pid_src += pid.next(pid_src, time);
    }

    TEST_ASSERT_EQUAL_DOUBLE(pid_setpoint, pid_src);
}

void test_pid_getters_and_setters(void)
{
    double pid_setpoint = 1.5, kp = 500, ki = 500, kd = 100;
    Core::Pid pid = Core::Pid(pid_setpoint, kp, ki, kd);

    TEST_ASSERT_EQUAL_DOUBLE(pid_setpoint, pid.getSetpoint());
    TEST_ASSERT_EQUAL_DOUBLE(kp, pid.getKp());
    TEST_ASSERT_EQUAL_DOUBLE(ki, pid.getKi());
    TEST_ASSERT_EQUAL_DOUBLE(kd, pid.getKd());

    pid.setSetpoint(pid_setpoint * 2);
    pid.setKp(kp * 2);
    pid.setKi(kp * 2);
    pid.setKd(kd * 2);

    TEST_ASSERT_EQUAL_DOUBLE(pid_setpoint * 2, pid.getSetpoint());
    TEST_ASSERT_EQUAL_DOUBLE(kp * 2, pid.getKp());
    TEST_ASSERT_EQUAL_DOUBLE(ki * 2, pid.getKi());
    TEST_ASSERT_EQUAL_DOUBLE(kd * 2, pid.getKd());
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_pid_works);
    RUN_TEST(test_pid_getters_and_setters);

    UNITY_END();
    return 0;
}