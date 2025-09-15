#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Replace with your WiFi credentials
const char* ssid = "SpektraAdmin-2.4Ghz@unifi";
const char* password = "SPEKTRA4419";

// Telegram bot details
#define BOTtoken "[TOKEN]"   // From BotFather
#define CHAT_ID "[ChatID]"      // From https://api.telegram.org/bot[TOKEN]/getUpdates

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

const int vibrationPin = D2;  // Vibration sensor digital pin
bool vibrationDetected = false;

void setup() {
  Serial.begin(115200);
  pinMode(vibrationPin, INPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  client.setInsecure(); // Skip certificate check
}

void loop() {
  int sensorValue = digitalRead(vibrationPin);

  if (sensorValue == HIGH && !vibrationDetected) {
    vibrationDetected = true;
    Serial.println("⚠️ Vibration detected!");
    bot.sendMessage(CHAT_ID, "⚠️ Vibration detected!", "");
  } 
  else if (sensorValue == LOW) {
    vibrationDetected = false; // Reset
  }

  delay(500);
}
