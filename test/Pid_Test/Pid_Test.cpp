#include <unity.h>
#include "Dynamics/Pid.hpp"
#include <Instance.hpp>

void setup(void)
{
}

void tearDown(void)
{
}

// constant parameters for each pid test fixture
static constexpr double setpoint = 1.5, kp = 500, ki = 500, kd = 100;

// ensure that pid converges on setpoint after n-iterations
void test_pid_converges(void)
{
    double pid_src = 0;
    Dynamics::Pid pid = Dynamics::Pid(setpoint, kp, ki, kd);

    // if working it should approach value
    const size_t iters = 100;
    for (size_t i = 0; i < iters; i++)
    {
        const unsigned long time = (i + 1) * 1000000;
        pid_src += pid.next(pid_src, time);
    }

    TEST_ASSERT_EQUAL_DOUBLE(setpoint, pid_src);
}

// test that pid parameter getters work as intended
void test_pid_getters(void)
{
    Dynamics::Pid pid = Dynamics::Pid(setpoint, kp, ki, kd);

    TEST_ASSERT_EQUAL_DOUBLE(setpoint, pid.getSetpoint());
    TEST_ASSERT_EQUAL_DOUBLE(kp, pid.getKp());
    TEST_ASSERT_EQUAL_DOUBLE(ki, pid.getKi());
    TEST_ASSERT_EQUAL_DOUBLE(kd, pid.getKd());
}

// test that pid parameter setters work as intended
void test_pid_setters(void)
{
    Dynamics::Pid pid = Dynamics::Pid(setpoint, kp, ki, kd);

    pid.setSetpoint(setpoint * 2);
    pid.setKp(kp * 2);
    pid.setKi(kp * 2);
    pid.setKd(kd * 2);

    TEST_ASSERT_EQUAL_DOUBLE(setpoint * 2, pid.getSetpoint());
    TEST_ASSERT_EQUAL_DOUBLE(kp * 2, pid.getKp());
    TEST_ASSERT_EQUAL_DOUBLE(ki * 2, pid.getKi());
    TEST_ASSERT_EQUAL_DOUBLE(kd * 2, pid.getKd());
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_pid_converges);
    RUN_TEST(test_pid_getters);
    RUN_TEST(test_pid_setters);

    UNITY_END();
    return 0;
}