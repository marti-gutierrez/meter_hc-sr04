#ifndef _UART_H_
#define _UART_H_

#define F_CPU 16000000UL
#define BAUD 9600
// sfr-bit
#define clear_bit(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define set_bit(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

// libraries
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdio.h>

void uart_init();
static int uart_putchar(char character, FILE *stream);
static int uart_getchar(FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

static FILE mystdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

// prototype
#endif // _UART_H_