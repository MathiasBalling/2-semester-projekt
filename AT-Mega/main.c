#include <stdint.h>
#define __AVR_ATmega644PA__
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define BAUD_RATE 9600 // Define the baud rate for UART communication
// #define UBRR_VAL ((F_CPU / (16 * BAUD_RATE)) - 1) // Calculate the UBRR value
#define UBRR_VAL 51

#define PWM_PIN PD5 // Define the PWM output pin
#define DIR_PIN PC2 // Define the direction pin
#define LED_PIN PB1 // Define the LED pin

void setup_adc() {
  ADMUX = (1 << REFS0) | (1 << ADLAR); // Set the reference voltage to AVCC
  ADCSRA = (1 << ADEN) | (1 << ADIE) | (0 << ADSC) | (1 << ADPS2) |
           (1 << ADPS1) |
           (1 << ADPS0); // Enable ADC and set the prescaler to 128
}
double pwm = 1;
void setup_pwm() {
  // Configure PD5 as output
  DDRD |= (1 << PWM_PIN);
  // Configure timer for PWM output on PD5
  TCCR1A |= (1 << COM1A1) | (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
  ICR1 = 0xFFFF;
}
// Sets up direction pin for motor
void setup_dir() {
  // Configure PC2 as output
  DDRC |= (1 << DIR_PIN);
}
// Sets up led pin
void setup_led() {
  // Configure PB1 as output
  DDRB |= (1 << LED_PIN);
}

void turn_on_led() {
  // Turn on the LED by setting PB1 high
  PORTB |= (1 << LED_PIN);
}

void turn_off_led() {
  // Turn off the LED by setting PB1 low
  PORTB &= (0 << LED_PIN);
}

// Enables the switching of direction
void set_direction(int dir) {
  if (dir) {
    // Set DIR_PIN high for forward direction
    PORTC |= (1 << DIR_PIN);
  } else {
    // Set DIR_PIN low for reverse direction
    PORTC &= ~(1 << DIR_PIN);
  }
}

void stop_motor() { OCR1A = 0; }

void set_pwm() {
  // Set the PWM duty cycle to 50%
  OCR1A = ICR1; // * pwm;
}

void grip() {
  set_direction(1);
  // Set the PWM duty cycle to 50%
  // OCR1A = ICR1 / 2;
  set_pwm();
}

void un_grip() {

  set_direction(0);
  // Set the PWM duty cycle to 50%
  // OCR1A = ICR1 / 2;
  set_pwm();
}

void setup_uart() {
  // Setup UART
  UBRR1H =
      (UBRR_VAL >> 8); // Set the UBRRH register with the high byte of the UBRR
  // value
  UBRR1L =
      UBRR_VAL; // Set the UBRRL register with the low byte of the UBRR value
  UCSR1B = (1 << TXEN1) | (1 << RXEN1) |
           (1 << RXCIE1); // Enable RX and TX and RX interrupt in UCSRB register
}

int main(void) {
  setup_dir();
  setup_led();
  setup_pwm();
  setup_adc();
  setup_uart();

  sei(); // Enable interrupts globally
  while (1) {
  }
}

////////////////// ISR Part //////////////////////

// UART receive interrupt service routine
ISR(USART1_RX_vect) {
  static uint8_t command_data;
  while (!(UCSR1A & (1 << RXC1))) {
  }
  command_data = UDR1; // Declare a static array to store the received bytes
  if (command_data) {
    grip();
    turn_on_led();
  } else {
    un_grip();
    turn_off_led();
  }
  while (ADCSRA & (1 << ADSC)) {
  }
  static uint8_t adc_val;
  adc_val = ADCH;
  UDR1 = adc_val;
  _delay_ms(1000);
  stop_motor();
}
// static uint8_t command_data;
// command_data = UDR1; // Declare a static array to store the received
// bytes if (command_data == 0) {
//   turn_off_led();
// } else if (command_data == 1) {
//   turn_on_led();
// }
// UDR1 = command_data; // Send the received byte back to the PC

ISR(ADC_vect) {
  // uint8_t adc_val = ADCH;
  // Start the next conversion
}