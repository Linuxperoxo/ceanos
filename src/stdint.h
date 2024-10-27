#ifndef STDINT_H
#define STDINT_H

#define BITMASK(x) (1<<(x))
#define BIT_TEST(val, x) ((val) & BITMASK(x))
#define BIT_SET(val, x) ((val) | BITMASK(x))
#define BIT_CLEAR(val, x) ((val) & ~BITMASK(x))
#define BIT_INVERT(val, x) ((val) ^ BITMASK(x))

#define NULL ((void*)0)

typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef signed long int int32_t;
typedef unsigned long int uint32_t;

typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;

typedef unsigned int size_t;

typedef unsigned long uintptr_t;
typedef long ptrdiff_t; 
typedef long long intmax_t;

typedef uint8_t bool;
#define true 1
#define false 0

#endif
