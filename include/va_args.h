#pragma once

#define va_start(v,l)  __builtin_va_start(v,l)
#define va_arg(v,l)    __builtin_va_arg(v,l)
#define va_end(v)      __builtin_va_end(v)
#define va_list        __builtin_va_list
