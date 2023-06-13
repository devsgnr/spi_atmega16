#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>

#include "lcdlib.h"   /* Header File - 16x2 LCD */
#include "spi_comm.h" /* Header File - SPI Master */

#define TIMER1_DELAY 0xF9E5 /* 100ms Delay - with 1024 Prescaler */
#define LED_PORT PA4

uint8_t intr_counter;
char* string_buffer;

ISR(TIMER1_OVF_vect) {
    TCNT1 = TIMER1_DELAY;
    PORTA ^= (1 << LED_PORT);
    intr_counter++;
}

int main(void) {
    LCD_Init();
    SPI_Init();

    DDRA = 0xFF; /* Set Port A as Output */

    LCD_String_xy(0, 0, "Master Device");
    LCD_String_xy(1, 0, "Sending Data:   ");

    TCNT1 = TIMER1_DELAY;
    TCCR1A = 0x00;
    TCCR1B = (1 << CS10) | (1 << CS12); /* Timer Mode - 1024 Prescaler */
    TIMSK = (1 << TOIE1);               /* Enable Overflow Interrupt */
    intr_counter = 0;
    sei();

    while (1) {
        SPI_DDR &= ~(1 << CS); /* Set Chip Select / Slave Select to Low */

        SPI_MasterTransmit(intr_counter); /* Transmit Data to Slave 1 */
        itoa((int)intr_counter, string_buffer, 10);
        LCD_String_xy(1, 13, string_buffer); /* Temperature Sensor to LCD */

        SPI_DDR |= (1 << CS); /* Set Chip Select / Slave Select to High */
    }
}