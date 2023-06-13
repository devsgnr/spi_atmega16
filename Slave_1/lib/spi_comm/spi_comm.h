#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define SPI_DDR DDRB
#define CS PINB4   /* Chip Select */
#define MOSI PINB5 /* Master Out Slave In */
#define MISO PINB6 /* Master In Slave Out */
#define SCK PINB7  /* Serial Clock */

void SPI_Init() {
    // Set CS, MOSI, and SCK to output
    SPI_DDR |= (1 << CS) | (1 << MOSI);
    // Enable SPI; set clock to fosc/128
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
}

uint8_t SPI_Recieve() {
    while (!(SPSR & (1 << SPIF))) {
    };
    return SPDR;
}