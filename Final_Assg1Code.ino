#include <Wire.h>             // Include Wire library for I2C communication
#include <Adafruit_GFX.h>     // Include Adafruit GFX library for graphics functions
#include <Adafruit_SSD1306.h> // Include Adafruit SSD1306 OLED library
#include <DHT.h>              // Include DHT sensor library
#define DHTPIN D4            // Define pin for DHT22 sensor
#define DHTTYPE DHT22         // Define type of DHT sensor
#define TRIGGER_PIN D6        // Define pin for HC-SR04 trigger
#define ECHO_PIN D7          // Define pin for HC-SR04 echo
#define OLED_RESET D3         // Define pin for OLED reset
#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Initialize OLED display object
DHT dht(DHTPIN, DHTTYPE);    // Initialize DHT sensor object

void setup() {
  Serial.begin(115200);        // Initialize serial communication
  pinMode(TRIGGER_PIN, OUTPUT); // Set trigger pin as output
  pinMode(ECHO_PIN, INPUT);  // Set echo pin as input
  dht.begin();               // Initialize DHT sensor
  
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Initialize OLED display
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  
  display.display();         // Display the splash screen
  delay(2000);
  display.clearDisplay();    // Clear the display buffer
}

void loop() {
  float temperature_C = dht.readTemperature();     // Read temperature in Celcius
  float temperature_F = dht.readTemperature(true); // Read temperature in Fahrenheit
  float humidity = dht.readHumidity();           // Read humidity from DHT sensor
  float distance = getDistance();                // Read distance from HC-SR04 sensor
 

  display.clearDisplay();                        // Clear the display buffer
  display.setTextSize(1);                        // Set text size
  display.setTextColor(SSD1306_WHITE);           // Set text color
  display.setCursor(0, 0);                      // Set cursor position
  display.print("Temp: ");                       // Print label for temperature
  display.print(temperature_C);                    // Print temperature value
  display.println(" C");                         // Print temperature unit
  display.print("Fahrenheit: ");                   // Print label for temperature
  display.print(temperature_F);                    // Print temperature value
  display.println(" F");                         // Print temperature unit
  display.print("Humidity: ");                   // Print label for humidity
  display.print(humidity);                        // Print humidity value
  display.println("%");                          // Print humidity unit
  display.print("Distance: ");                   // Print label for distance
  display.print(distance);                        // Print distance value
  display.println(" cm");                        // Print distance unit
  display.display();                             // Update OLED display
  delay(2000);                                   // Delay for 2 seconds
}


float getDistance() {
  digitalWrite(TRIGGER_PIN, LOW);                // Set trigger pin to LOW
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);               // Set trigger pin to HIGH
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);                // Set trigger pin to LOW
  long duration = pulseIn(ECHO_PIN, HIGH);       // Measure duration of pulse
  float distance = duration * 0.034 / 2;         // Calculate distance
  return distance;                               // Return distance value
}
