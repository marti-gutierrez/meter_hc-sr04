/*
El siguiente programa prende y apaga un led conectado al pin 13 (PB5) de la placa Arduino UNO (ATmega328P).
*/

#define pin_trigger PC1
#define pin_echo PC0

#include "header.h"
#include <avr/io.h>
#include <util/delay.h>
#include <uart.h>

void HC_SR04_pulse();
float HC_SR04_distance();

int main(void)
{
  set_bit(DDRC, pin_trigger); // Pin 13 como salida
  clear_bit(PORTC, pin_trigger);
  clear_bit(DDRC, pin_echo); // Pin 12 como entrada
  uart_init();
  while (1)
  {
    printf("\n The distance is: %0.2f cm\n", HC_SR04_distance());
    _delay_ms(1000);
  }
}

void HC_SR04_pulse()
{
  TCNT1H = 0x00;
  TCNT1L = 0x00;
  set_bit(PORTC, pin_trigger);
  _delay_us(10);
  clear_bit(PORTC, pin_trigger);
  _delay_us(220);
  loop_until_bit_is_set(PINC, pin_echo);
  TCCR1B = (0 << CS12) | (1 << CS11) | (1 << CS10); // Prescaler 64
  loop_until_bit_is_clear(PINC, pin_echo);
  TCCR1B = (0 << CS12) | (0 << CS11) | (0 << CS10);
}

float HC_SR04_distance()
{
  HC_SR04_pulse();
  return TCNT1 * 4 * 0.034 / 2;
}
