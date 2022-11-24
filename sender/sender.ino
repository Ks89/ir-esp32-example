#include <WiFi.h>

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Coolix.h>


#define SECRET_SSID "<ADD YOUR WIFI SSID HERE>"
#define SECRET_PASS "<ADD YOUR WIFI PASSWORD HERE>"


// ------------------------------------------------------
// ------------------ IRremoteESP8266 -------------------
#define SEND_COOLIX
#define HEAT_MODE kCoolixHeat
#define FAN_AUTO kCoolixFanAuto
struct state {
  uint8_t temperature = 28, fan = 0, operation = 0;
  bool powerStatus;
};
state acState;
#define IR_SEND_PIN 4 // ESP GPIO pin to use to send IR signals
IRCoolixAC ac(IR_SEND_PIN); // Create a A/C object using GPIO to sending messages with
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ----------------------- WIFI -------------------------
const char* ssid = SECRET_SSID; 
const char* password = SECRET_PASS;
String macAddress;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("--------------- WiFi ----------------");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  delay(2000);
  Serial.println("Wifi OK, initializing AC");

  ac.begin();
  delay(1000);

  ac.on();
  ac.setTemp(20);
  ac.setFan(FAN_AUTO);
  ac.setMode(HEAT_MODE);
  
  Serial.println("Initialized");
  delay(1500);
}

void loop() {
  Serial.println("Sending...");

  ac.send();

  delay(1000);
}