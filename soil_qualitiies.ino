 #include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT11.h>

// Pin definitions
#define phPin A1
#define moisturePin A3
#define rainPin A2
#define modem_Switch 4
#define modemRX 7
#define modemTX 8

// Constants
const unsigned long alertInterval = 300000; // 5 minutes for SMS alerts
const unsigned long displayToggleInterval = 10000; // 5 seconds for screen toggle
const float calibration_value = 21.34; // pH sensor calibration

// Global variables
DHT11 dht11(9);
LiquidCrystal_I2C screen(0x27, 20, 4);
SoftwareSerial modem(modemRX, modemTX);
unsigned long lastAlertTime = 0;
unsigned long lastDisplayToggleTime = 0;
bool showSensors = true;
int buffer_arr[10], temp;
float temperature = 0, humidity = 0, moistureSens = 0, rainSens = 0, ph = 0;

void setup() {
  Serial.begin(115200);
  modem.begin(9600);

  pinMode(moisturePin, INPUT);
  pinMode(rainPin, INPUT);
  pinMode(modem_Switch, OUTPUT);
  digitalWrite(modem_Switch, HIGH);
  
  screen.init();
  screen.backlight();
  displayWelcomeMessage();
  
  modemTest();
  delay(1000);
  screen.clear();
}

void loop() {
  unsigned long currentTime = millis();
  
  // Read sensors continuously
  readAllSensors();
  
  // Toggle display every 5 seconds
  if (currentTime - lastDisplayToggleTime >= displayToggleInterval) {
    showSensors = !showSensors;
    lastDisplayToggleTime = currentTime;
    screen.clear();
    
    if (showSensors) {
      displaySensorValues();
    } else {
      displayAdvice();
    }
  }
  
  // Send SMS alert every 5 minutes
  if (currentTime - lastAlertTime >= alertInterval) {
    sendAlertSMS();
    lastAlertTime = currentTime;
  }
  
  delay(100); // Small delay to prevent flickering
}
