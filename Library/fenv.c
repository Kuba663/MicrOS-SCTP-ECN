#include "fenv.h"

// Floating-point exceptions

int feclearexcept(int excepts)
{
    if(excepts == 0)
    {
        return 0;
    }
    // We only have 6 excepts to clear to cut varaible.
    unsigned char excepts_to_clear = (unsigned char)excepts;

    // Get current environment of FPU.
    fenv_t env;
    env = _FPU_read_enviroment();

    // Set first 2 digit as 0 to make sure we won't overwrite anything in first 2 bits.
    excepts_to_clear &= 0x3F;

    // Negate value.
    excepts_to_clear = ~excepts_to_clear;

    // And excepts_to_clear and current enviroment.
    fexcept_t * fe = &env.status_word;
    ((unsigned char *)fe)[0] &= excepts_to_clear;
    _FPU_write_control(env);
    return 0;
}

int fegetexceptflag(fexcept_t *flagp, int excepts)
{
    if(flagp == NULL)
    {
        return 1;
    }
    if(excepts == 0)
    {
        return 0;
    }
    // We only have 6 excepts to get to cut varaible.
    unsigned char excepts_to_get = (unsigned char)excepts;
    excepts_to_get &= 0x3F;

    // Get exceptions flags
    fexcept_t exceptions = _FPU_read_status_word();

    // Set only flags user asked for.

    if(excepts_to_get & 0x01)
    {
        flagp->invalid_operation = exceptions.invalid_operation;
    }
    if(excepts_to_get & 0x02)
    {
        flagp->denormalized_operand = exceptions.denormalized_operand;
    }
    if(excepts_to_get & 0x04)
    {
        flagp->zero_divide = exceptions.zero_divide;
    }
    if(excepts_to_get & 0x08)
    {
        flagp->overflow = exceptions.overflow;
    }
    if(excepts_to_get & 0x10)
    {
        flagp->underflow = exceptions.underflow;
    }
    if(excepts_to_get & 0x20)
    {
        flagp->precision = exceptions.precision;
    }
    return 0;
}

int feraiseexcept(int excepts)
{
    if(excepts == 0)
    {
        return 0;
    }
    // We only have 6 excepts to raise.
    unsigned char excepts_to_raise = (unsigned char)excepts;
    excepts_to_raise &= 0x3F;

    // Get current environment of FPU.
    fenv_t env;
    env = _FPU_read_enviroment();

    // Set exception flags.
    fexcept_t * fe = &env.status_word;
    ((unsigned char *)fe)[0] |= excepts_to_raise;
    _FPU_write_control(env);
    return 0;
}

int fesetexceptflag(const fexcept_t *flagp, int excepts)
{
    if(flagp == NULL)
    {
        return 1;
    }
    if(excepts == 0)
    {
        return 0;
    }
    // We only have 6 excepts to set.
    unsigned char excepts_to_set = (unsigned char)excepts;
    excepts_to_set &= 0x3F;

    // Get exceptions flags
    fenv_t env;
    env = _FPU_read_enviroment();

    // Set only flags user asked for.

    if(excepts_to_set & 0x01)
    {
        env.status_word.invalid_operation = flagp->invalid_operation;
    }
    if(excepts_to_set & 0x02)
    {
        env.status_word.denormalized_operand = flagp->denormalized_operand;
    }
    if(excepts_to_set & 0x04)
    {
        env.status_word.zero_divide = flagp->zero_divide;
    }
    if(excepts_to_set & 0x08)
    {
        env.status_word.overflow = flagp->overflow;
    }
    if(excepts_to_set & 0x10)
    {
        env.status_word.underflow = flagp->underflow;
    }
    if(excepts_to_set & 0x20)
    {
        env.status_word.precision = flagp->precision;
    }
    _FPU_write_control(env);
    return 0;
}

// Rounding direction

int fegetround(void)
{
    fcontrol_t control_word;
    control_word = _FPU_read_control_word();

    return control_word.rounding_control;
}

// Additional content

fcontrol_t _FPU_read_control_word()
{
    fcontrol_t control_word;

    __asm__ (
        "fstcw %0 \n"
        : "=m"(control_word));
    return control_word;

}

void _FPU_write_control_word(fcontrol_t control_word)
{
    __asm__ (
        "fclex \n" \
        "fldcw %0"
        :: "m"(control_word));
}

fenv_t _FPU_read_enviroment()
{
    fenv_t enviroment;

    __asm__ (
        "fstenv %0 \n"
        : "=m"(enviroment));
    return enviroment;
}

void _FPU_write_control(fenv_t enviroment)
{
    __asm__ (
        "fldenv %0"
        :: "m"(enviroment));
}

fexcept_t _FPU_read_status_word()
{
    fexcept_t status_word;

    __asm__ (
        "fstsw %0 \n"
        : "=m"(status_word));
    return status_word;
}

void _FPU_clear_exceptions()
{
    __asm__ (
        "fclex"
        ::);
}