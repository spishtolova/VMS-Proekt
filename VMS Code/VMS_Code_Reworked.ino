// Pin Definitions
#define RELAY_FAN 5        // Digital pin connected to the fan relay
#define RELAY_HEATER 4     // Digital pin connected to the heater relay
#define RELAY_VENT 6       // Digital pin connected to the ventilation system relay
#define BUZZER 7           // Digital pin connected to a buzzer

// Variables to store sensor readings
float temperature;
float humidity;
int airQuality;

// Thresholds
const int airQualityThreshold1 = 150;  // Threshold for moderate air quality (PPM)
const int airQualityThreshold2 = 200;  // Threshold for poor air quality (PPM)

void setup() {
  Serial.begin(9600);                // Start serial communication at 9600 baud
  pinMode(RELAY_FAN, OUTPUT);        // Set fan relay pin as output
  pinMode(RELAY_HEATER, OUTPUT);     // Set heater relay pin as output
  pinMode(RELAY_VENT, OUTPUT);       // Set ventilation relay pin as output
  pinMode(BUZZER, OUTPUT);           // Set buzzer pin as output
  digitalWrite(RELAY_FAN, LOW);      // Start with fan off
  digitalWrite(RELAY_HEATER, LOW);   // Start with heater off
  digitalWrite(RELAY_VENT, LOW);     // Start with ventilation system off
  digitalWrite(BUZZER, LOW);         // Start with buzzer off
}

void loop() {
  // Simulate sensor readings
  temperature = random(15, 30); // Random temperature between 15 and 30°C
  humidity = random(30, 70);    // Random humidity between 30% and 70%
  airQuality = random(100, 250); // Random air quality between 100 and 250 PPM

  // Print the sensor values to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Air Quality: ");
  Serial.print(airQuality);
  Serial.println(" PPM");

  // Control fan and heater based on temperature
  if (temperature > 25.0) {
    digitalWrite(RELAY_FAN, HIGH);  // Turn on the fan
    digitalWrite(RELAY_HEATER, LOW); // Turn off the heater
  } else if (temperature < 18.0) {
    digitalWrite(RELAY_HEATER, HIGH); // Turn on the heater
    digitalWrite(RELAY_FAN, LOW);     // Turn off the fan
  } else {
    digitalWrite(RELAY_FAN, LOW);     // Turn off the fan
    digitalWrite(RELAY_HEATER, LOW);  // Turn off the heater
  }

  // Control ventilation and alarm based on air quality
  if (airQuality > airQualityThreshold2) {
    digitalWrite(RELAY_VENT, HIGH);   // Turn on the ventilation system
    digitalWrite(BUZZER, HIGH);       // Turn on the buzzer to signal very poor air quality
  } else if (airQuality > airQualityThreshold1) {
    digitalWrite(RELAY_VENT, HIGH);   // Turn on the ventilation system
    digitalWrite(BUZZER, LOW);        // Keep the buzzer off for moderate air quality
  } else {
    digitalWrite(RELAY_VENT, LOW);    // Turn off the ventilation system
    digitalWrite(BUZZER, LOW);        // Turn off the buzzer
  }

  // Wait for a minute before next reading
  delay(60000);
}