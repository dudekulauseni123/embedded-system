#include <Arduino.h>
#include <SPI.h>

#define PIN_CS 10
#define BUFFER_SIZE 32*8

char buf[BUFFER_SIZE];
SPISettings mySetting(1000000, MSBFIRST, SPI_MODE0);

volatile byte pos;
volatile bool process_it;

void setup() {
    Serial.begin(9600);
    pinMode(PIN_CS, OUTPUT);
    pinMode(MISO, OUTPUT);
    SPCR |= _BV(SPE);
    SPCR |= _BV(SPIE);
    pos = 0;
    process_it = false;
}

ISR (SPI_STC_vect) {
    byte c = SPDR;
    if (pos < sizeof(buf)) {
        buf[pos++] = c;
        if (c == '\n')
            process_it = true;
    }
}

void loop() {
    if (process_it) {
        buf[pos] = 0;
        Serial.print(buf);
        pos = 0;
        process_it = false;
    }
}