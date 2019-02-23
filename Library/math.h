#include<float.h>

#ifndef MATH_H
#define MATH_H

#define M_E         2.7182818284590452354
#define M_LOG2E     1.4426950408889634074
#define M_LOG10E    0.43429448190325182765
#define M_LN2       0.69314718055994530942
#define M_LN10      2.30258509299404568402
#define M_PI        3.14159265358979323846
#define M_PI_2      1.57079632679489661923
#define M_PI_4      0.78539816339744830962
#define M_1_PI      0.31830988618379067154
#define M_2_PI      0.63661977236758134308
#define M_2_SQRTPI  1.12837916709551257390
#define M_SQRT2     1.41421356237309504880
#define M_SQRT1_2   0.70710678118654752440

// Trigonometric functions

double cos(double x);
float cosf(float x);

double sin(double x);
float sinf(float x);

double tan(double x);
float tanf(float x);

double acos(double x);
float acosf(float x);

double asin(double x);
float asinf(float x);

double atan(double x);
float atanf(float x);

double atan2(double x, double y);
float atan2f(float x, float y);

// Hyperbolic functions

double cosh(double x);
float coshf(float x);

double sinh(double x);
float sinhf(float x);

double tanh(double x);
float tanhf(float x);

double acosh(double x);
float acoshf(float x);

double asinh(double x);
float asinhf(float x);

double atanh(double x);
float atanhf(float x);

// Exponential and logarithmic functions

double exp(double x);
float expf(float x);

double log(double x);
float logf(float x);

double log10(double x);
float log10f(float x);

double modf(double x, double* intpart);
float modff(float x, float* intpart);

double exp2(double x);
float exp2f(float x);

double expm1(double x);
float expm1f(float x);

double log1p(double x);
float log1pf(float x);

double log2(double x);
float log2f(float x);

double logb(double x);
float logbf(float x);

// Power functions 

double pow(double base, double exponent);
float powf(float base, float exponent);

double sqrt(double x);
float sqrtf(float x);

// Nearest integer floating-point operations

double ceil(double x);
float ceilf(float x);

double floor(double x);
float floorf(float x);

double trunc(double x);
float truncf(float x);

double round(double x);
float roundf(float x);

// Other functions

double fabs(double x);
float fabsf(float x);

// Helpers ------------------------------------------

// Values for FPU Control Word

#define _FPU_precision_single 0
#define _FPU_precision_double 1
#define _FPU_precision_extended 3

#define _FPU_rounding_nearest_even 0
#define _FPU_rounding_floor 1
#define _FPU_rounding_ceil 2
#define _FPU_rounding_truncate 3

#define _FPU_infinity_control_projective 0
#define _FPU_infinity_control_affine 1

typedef struct _FPU_status_word
{
	unsigned char invalid_operation : 1;
	unsigned char denormalized_operand : 1;
	unsigned char zero_divide : 1;
	unsigned char overflow : 1;
	unsigned char underflow : 1;
	unsigned char precision : 1;
	unsigned char stack_fault : 1;
	unsigned char error_summary_status : 1;
	unsigned char condition_code_0: 1;
	unsigned char condition_code_1: 1;
	unsigned char condition_code_2: 1;
	unsigned char top_of_stack_pointer : 3;
	unsigned char condition_code_3: 1;
	unsigned char busy : 1;
} _FPU_status_word;

typedef struct _FPU_control_word
{
	unsigned char invalid_operation : 1;
	unsigned char denormalized_operand : 1;
	unsigned char zero_divide : 1;
	unsigned char overflow : 1;
	unsigned char underflow : 1;
	unsigned char precision : 1;
	unsigned char : 2;
	unsigned char precision_control : 2;
	unsigned char rounding_control : 2;
	unsigned char infinity_control : 1;
	unsigned char : 3;
} _FPU_control_word;

_FPU_control_word _FPU_read_control_word();
void _FPU_write_control_word(_FPU_control_word control_word);
_FPU_status_word _FPU_read_status_word();
void _FPU_clear_exceptions();

#endif