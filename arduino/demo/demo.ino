
#define PIN10 (1 << 2)
#define PIN11 (1 << 3)

const int PIN_LED = 10;
const int PIN_BUTTON = 11;

void setup_app() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
}

inline void z80_out(char data) {
  if (data & 1) {
    PORTB |= PIN10;
  } else {
    PORTB &= ~PIN10;
  }
}

inline char z80_in() {
  return (PINB & PIN11) ? 0 : 1;
}

//---------------------------------------

#define PIN8 (1 << 0)
#define PIN9 (1 << 1)

void setup() {
  setup_app();
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  // Configure pins 0-7 as input
  DDRD = 0;
  noInterrupts();
}

void loop() {
  // Wait for ARDUINO_SEL_N to go low
  while (PINB & PIN8) ;
  if (PINB & PIN9) {
    // Read from I/O bus
    z80_out(PIND);
  } else {
    // Write to I/O bus
    DDRD = 0xff;
    PORTD = z80_in();
  }
  // Wait for ARDUINO_SEL_N to go high
  while (!(PINB & PIN8)) ;
  DDRD = 0;
}
