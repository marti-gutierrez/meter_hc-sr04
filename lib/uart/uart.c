#include "uart.h"

void uart_init()
{
  set_bit(DDRD, PD1);                        // PD1(Tx) --> outPut
  clear_bit(DDRD, PD0);                      // PD0(Rx) <-- inPut
  clear_bit(UCSR0A, U2X0);                   // 1. Desactivate double speed transmission. (optional)
  UCSR0B |= _BV(RXEN0) | _BV(TXEN0);         // 2. enable Receiver and transmitter.
  UCSR0C |= (0 << UMSEL01) | (0 << UMSEL01); // 3. Activate Asynchronous UART
  UCSR0C |= (0 << UPM01) | (0 << UPM00);     // 4. Parity: Disabled
  clear_bit(UCSR0C, USBS0);                  // 5. Stop bit: 1-bit
  clear_bit(UCSR0B, UCSZ02);
  UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00); // 6. Character size: 8-bits
  UBRR0H = UBRRH_VALUE;                // 7. Baud Rate: 9600
  UBRR0L = UBRRL_VALUE;                // 7. Baud Rate: 9600
  stdout = &mystdout;
  stdin = &mystdin;
}

static int uart_putchar(char character, FILE *stream)
{
  if (character == '\n')
    uart_putchar('\r', stream);
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = character;
  return 0;
}

static int uart_getchar(FILE *stream)
{
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}