#pragma once
#include "types.h"

void uart_init();
void uart_send(char c);
char uart_recv();

void putchar(char c);
