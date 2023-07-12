#include <Arduino.h>
#include <SPI.h>

#define PIN_CS 10
#define BUFFER_SIZE 32*8

char buf[BUFFER_SIZE];

volatile int pos;

void setup() {
    Serial.begin(9600);
    pinMode(PIN_CS, OUTPUT);
    pinMode(MISO, OUTPUT);
    SPCR |= _BV(SPE);
    SPCR |= _BV(SPIE);
    pos = 0;
}

ISR (SPI_STC_vect) {
    byte c = SPDR;
    if (pos < BUFFER_SIZE) {
        buf[pos++] = c;
        if (c == '\n') {
            buf[pos] = 0;
            Serial.print(buf);
            pos = 0;
        }
    }
}

void loop() {}