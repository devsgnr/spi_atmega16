#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "lcdlib.h"
#include "spi_comm.h"

#define TIMER1_DELAY 0xF9E5 /* 100ms Delay - with 1024 Prescaler */

char* string_buffer;
uint8_t recived_value;

ISR(TIMER1_CAPT_vect) { TCNT1 = TIMER1_DELAY; }

int main(void) {
    LCD_Init();
    SPI_Init();

    LCD_String_xy(0, 0, "Slave Device");
    LCD_String_xy(1, 0, "Recieved Data:   ");

    TCNT1 = TIMER1_DELAY;
    TCCR1A = 0x00;
    TCCR1B = (1 << CS10) | (1 << CS12); /* Timer Mode - 1024 Prescaler */
    TIMSK = (1 << TOIE1);               /* Enable Overflow Interrupt */

    while (1) {
        itoa((int)SPI_Recieve(), string_buffer, 10); /* Recieve & Display */
        LCD_String_xy(1, 14, string_buffer);         /* Display to LCD */
    }
}