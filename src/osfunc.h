#pragma once

#include "stdint.h"

void _term_help();
void set_color(uint8_t color); 
void itoa(int value, char* str, int base); 
void _get_sysinfo();
void halt();
