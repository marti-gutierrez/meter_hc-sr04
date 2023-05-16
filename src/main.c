/*
El siguiente programa prende y apaga un led conectado al pin 13 (PB5) de la placa Arduino UNO (ATmega328P).
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  // Configurar el pin 13 (PB5) como salida
  DDRB |= (1 << PB5);
  while (1)
  {
    // Toggle del pin 13 (PB5)
    PORTB |= (1 << PB5);
    _delay_us(10);
    PORTB &= ~(1 << PB5);
    _delay_ms(2000);
    // Esperar 1 segundo
  }
}