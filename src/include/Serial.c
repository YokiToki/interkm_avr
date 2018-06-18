#include <stdio.h>
#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define BAUD 9600

void serial_init()
{
    /* calculate and set the baudrate */
    uint16_t baud = (F_CPU / 8 / BAUD - 1) / 2; 
    UBRR0H = (uint8_t) (baud >> 8);
    UBRR0L = (uint8_t) (baud & 0x0ff);  

    /* activate transmitter, receiver and receiver interrupt */
    UCSR0B |= (1 << 3); /* TXEN */
    UCSR0B |= (1 << 4); /* RXEN */
    UCSR0B |= (1 << 7); /* RXCIE */

    /* set 8 data bits */
    UCSR0C |=  (1 << 1); /* UCSZ0 = 1 */
    UCSR0C |=  (1 << 2); /* UCSZ1 = 1 */
    UCSR0B &= ~(1 << 2); /* UCSZ2 = 0 */

    /* set parity NONE */
    UCSR0C &= ~(1 << 4); /* UPM0 = 0 */
    UCSR0C &= ~(1 << 5); /* UPM1 = 0 */

    /* set 1 stopbit */
    UCSR0C |=  (1 << 3); /* USBS = 1 */
}

int serial_write(char c, FILE *stream) {
    if (c == '\n') {
        serial_write('\r', stream);
    }
    loop_until_bit_is_set(UCSR0A, UDRE0); // while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;

    return 0;
}

int serial_read(FILE *stream) {
    loop_until_bit_is_set(UCSR0A, RXC0); // while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}
