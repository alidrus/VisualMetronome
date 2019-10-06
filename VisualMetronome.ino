// vim: autoindent smartindent syntax=cpp expandtab tabstop=4 shiftwidth=4 softtabstop=4:

/*
 */

int dataPin   = 11, // ATmega328 pin 17 -> 74HC595 pin 14
    latchPin  =  8, // ATmega328 pin 14 -> 74HC595 pin 12
    clockPin  = 12; // ATmega328 pin 18 -> 74HC595 pin 11

bool leftDirection = true;

unsigned long period,
              periodDivide7,
              periodRemainder,
              adjustment;

// The song's beats per minute
int songBPM = 89;

// The shift register LEDs
byte leds = 0B00000001;

void setup() {
    // initialize LED digital pins as output.
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    // beat periods
    period          = (unsigned long) 60000000 / songBPM;
    periodDivide7   = period / 7;
    periodRemainder = period - (periodDivide7 * 7) + (60000000 - period * songBPM);

}

void loop() {
    unsigned long currentMicros;

    for (int i = 0; i < 7; i++)
    {
        currentMicros = micros();

        updateLEDs();

        leds = leds << 1;

        while(micros() < (currentMicros + periodDivide7)) {
        }
    }

    delayMicroseconds(periodRemainder);

    for (int i = 0; i < 7; i++)
    {
        currentMicros = micros();

        updateLEDs();

        leds = leds >> 1;

        while(micros() < (currentMicros + periodDivide7)) {
        }
    }

    delayMicroseconds(periodRemainder);
}

void updateLEDs() {
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(latchPin, LOW);

        shiftOut(dataPin, clockPin, MSBFIRST, leds);

        digitalWrite(latchPin, HIGH);
    }
}
