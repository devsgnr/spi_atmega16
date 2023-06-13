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
    SPI_DDR |= (1 << CS) | (1 << MOSI) | (1 << SCK);
    // Enable SPI; set as Master and clock to fosc/128
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
}

void SPI_MasterTransmit(uint8_t data) {
    // Load data into register
    SPDR = data;
    // Wait for transmission to complete
    while (!(SPSR & (1 << SPIF))) {
    };
}