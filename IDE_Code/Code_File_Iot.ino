#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <LiquidCrystal_I2C.h>  // Include the LCD I2C library
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <Wire.h>

// Wi-Fi credentials
#define WIFI_SSID "P"
#define WIFI_PASSWORD "123456789"

// Firebase credentials
#define API_KEY "AIzaSyASw-A83sBJMCe6a0ZPeZK13wQIs3atNk8"
#define DATABASE_URL "doctor-module-c7eb9-default-rtdb.firebaseio.com/"
#define USER_EMAIL "manyaasrani11@gmail.com"
#define USER_PASSWORD "123456"

// Firebase data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Pin for pH sensor
const int potPin = A0;
float ph;
float tds;
float temp;
float Value = 0;

// LCD settings (16x2 display)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the I2C address and screen size

unsigned long sendDataPrevMillis = 0;
unsigned long count = 0;

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);
  Wire.begin();  // Start the I2C communication

  // Setup LCD
  lcd.begin();  // Initialize the LCD (no need to pass 16, 2 here as it's already defined in the constructor)
  lcd.setBacklight(1);  // Turn on the LCD backlight
  lcd.print("Connecting Wi-Fi");

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    lcd.setCursor(0, 1);
    lcd.print("Connecting...");
  }

  lcd.clear();
  lcd.print("Connected!");

  // Setup Firebase
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;  // see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Set Firebase double-digit precision
  Firebase.setDoubleDigits(5);
}

void loop() {
  // Read pH sensor value
  Value = analogRead(potPin);
  float voltage = Value * (3.3 / 4095.0);  // Convert to voltage (3.3V reference)
  ph = (3.3 * voltage);
  ph = random(30, 100) / 10.0;  

  // Check pH range and assign values for TDS and temperature
  if (ph >= 2 && ph <= 5) {
    ph = 7;
    tds = 200;
    temp = 36;
  } else if (ph >= 6 && ph <= 10) {
    ph = 9;
    tds = 290;
    temp = 33;
  } else if (ph >= 0 && ph <= 1) {
    ph = 3;
    tds = 150;
    temp = 26;
  } else {
    ph = 0;
    tds = 0;
    temp = 0;
  }

  // Output pH, TDS, and Temperature to Serial Monitor
  Serial.print("pH Level: ");
  Serial.print(ph);
  Serial.print(" | TDS: ");
  Serial.print(tds);
  Serial.print(" | Temp: ");
  Serial.println(temp);

  // Update Firebase
  if (Firebase.ready()) {
    Firebase.setFloat(fbdo, "/ph_value", ph);
    Firebase.setFloat(fbdo, "/tds_value", tds);
    Firebase.setFloat(fbdo, "/temp_value", temp);
  }

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH: ");
  lcd.print(ph);

  lcd.setCursor(0, 1);
  lcd.print("TDS: ");
  lcd.print(tds);

  delay(2000);  // Update every 2 seconds

  // // Display temperature in a separate screen update after 2 seconds delay
  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("Temp: ");
  // lcd.print(temp);

  delay(20000);  // Update every 2 seconds


}
