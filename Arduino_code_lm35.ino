//temperature sensor using LM35 blinking of an LED using Arduino's timer output pins


// Define the analog pin for LM35 temperature sensor
const int lm35Pin = A0;

// Define the onboard LED pin
const int ledPin = 13;

// Variables to store temperature and previous time
float temperatureCelsius;
int blinkInterval = 250; // Initial blink interval

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Set up Timer1
  TCCR1A = 0;             // Clear Timer1 control register A
  TCCR1B = 0;             // Clear Timer1 control register B
  TCNT1 = 0;              // Initialize counter value to 0
  TCCR1B |= (1 << WGM12); // Configure Timer1 for CTC mode
  OCR1A = 15624;          // Set CTC compare value to 1Hz at 16MHz AVR clock, with a prescaler of 256
  TCCR1B |= (1 << CS12);  // Start Timer1 with prescaler 256
  TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare interrupt
}

void loop() {
  // Read the analog value from LM35 sensor
  int sensorValue = analogRead(lm35Pin);

  // Convert the analog value to temperature in Celsius
  temperatureCelsius = (sensorValue * 5.0 * 100.0) / 1024.0;

  // Print temperature to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureCelsius);
  Serial.println(" °C");

  // Check temperature conditions and update blink interval
  if (temperatureCelsius < 30) {
    blinkInterval = 250;
  } else {
    blinkInterval = 500;
  }
}

// Timer1 compare interrupt service routine
ISR(TIMER1_COMPA_vect) {
  // Toggle LED state
  digitalWrite(ledPin, !digitalRead(ledPin));
}
