//the Arduino code for temperature sensor LM35
// Define the analog pin for LM35 temperature sensor
const int lm35Pin = A0;

// Define the onboard LED pin
const int ledPin = 13;

// Variables to store temperature and blink interval
float temperatureCelsius;
int LEDblink = 250; // Initial blink interval
void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
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
  
  // Check temperature conditions and update LED blinK
  if (temperatureCelsius < 30) {
    LEDblink = 250;
  } else {
    LEDblink = 500;
  }
  
  // Blink LED according to LEDblink
  digitalWrite(ledPin, HIGH);
  delay(LEDblink);
  digitalWrite(ledPin, LOW);
  delay(LEDblink);
}