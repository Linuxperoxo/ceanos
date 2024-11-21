#ifndef __MATH_H__
#define __MATH_H__

#define M_E        2.71828182845904523536 
#define M_LOG2E    1.44269504088896340736  
#define M_LOG10E   0.43429448190325182765  
#define M_LN2      0.69314718055994530942  
#define M_LN10     2.30258509299404568402  
#define M_PI       3.14159265358979323846  
#define M_PI_2     1.57079632679489661923  
#define M_PI_4     0.78539816339744830962  
#define M_1_PI     0.31830988618379067154  
#define M_2_PI     0.63661977236758134308  
#define M_2_SQRTPI 1.12837916709551257390  
#define M_SQRT2    1.41421356237309504880  
#define M_SQRT1_2  0.70710678118654752440 

#define HUGE_VAL   (__builtin_huge_val()) 
#define HUGE_VALF  (__builtin_huge_valf()) 
#define HUGE_VALL  (__builtin_huge_vall()) 
#define INFINITY   (__builtin_inff())      
#define NAN        (__builtin_nanf(""))    

#define FP_INFINITE  1 
#define FP_NAN       2 
#define FP_NORMAL    3 
#define FP_SUBNORMAL 4 
#define FP_ZERO      5 

inline double fmod(double x, double y);
inline double fabs(double x);
double sqrt(double n);

#endif
