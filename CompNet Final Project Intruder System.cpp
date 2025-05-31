/*************************************************************
 * ESP32 Intruder Detection System with Blynk
 * Virtual Pin Assignment:
 * - V0: Red LED (Intruder Status)
 * - V1: Green LED (System Status)
 * - V2: Blue LED (Blynk Connection)
 * - V5: Buzzer Control Switch
 * 
 * Blynk Template Configuration:
 * - Required for Blynk.Cloud
 *************************************************************/

#define BLYNK_TEMPLATE_ID "TMPL6vbqfhpl6"
#define BLYNK_TEMPLATE_NAME "Intruder Burglary System"
#define BLYNK_AUTH_TOKEN "6tN40c9LCumQyXID5Qvs4SMZDM-wwbWs"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// ==== WiFi Configuration ====
char ssid[] = "keii";
char pass[] = "lalalala";

// Hardware Pins
#define RED_PIN     16
#define GREEN_PIN   17
#define BLUE_BLYNK  12
#define TRIG_PIN    26
#define ECHO_PIN    25
#define BUZZER_PIN  14

// Constants
#define SOUND_SPEED 0.034
#define DISTANCE_THRESHOLD 50
#define BLYNK_BLINK_INTERVAL 500

// Global Variables
float distance;
bool isBlynkConnected = false;
bool systemEnabled = true;

// Blynk Handlers
BLYNK_CONNECTED() {
  isBlynkConnected = true;
  Blynk.syncVirtual(V5);  // Sync switch state
  Blynk.virtualWrite(V2, 1);
  Serial.println("Connected to Blynk");
}

BLYNK_DISCONNECTED() {
  isBlynkConnected = false;
  Blynk.virtualWrite(V2, 0);
  Serial.println("Disconnected from Blynk");
}

BLYNK_WRITE(V5) {  // Master Switch
  systemEnabled = param.asInt();
  Serial.println(systemEnabled ? "System ENABLED" : "System DISABLED");
  
  if (!systemEnabled) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V1, 0);
  } else {
    digitalWrite(GREEN_PIN, HIGH);
    Blynk.virtualWrite(V1, 1);
  }
}

void setup() {
  Serial.begin(115200);
  
  // Initialize pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_BLYNK, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initial states
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_BLYNK, HIGH);
  digitalWrite(BUZZER_PIN, LOW);

  // WiFi Configuration
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Initialize Blynk widgets
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 1);
  Blynk.virtualWrite(V2, 0);
  Serial.println("System Initialized");
}

void loop() {
  Blynk.run();
  
  if (systemEnabled) {
    updateConnectionLED();
    checkIntruder();
  }
  delay(200);
}

void updateConnectionLED() {
  static unsigned long lastBlink = 0;
  static bool blinkState = false;

  if (isBlynkConnected) {
    if (millis() - lastBlink > BLYNK_BLINK_INTERVAL) {
      blinkState = !blinkState;
      digitalWrite(BLUE_BLYNK, blinkState);
      lastBlink = millis();
    }
    Blynk.virtualWrite(V2, blinkState);
  } else {
    digitalWrite(BLUE_BLYNK, HIGH);
    Blynk.virtualWrite(V2, 0);
  }
}

void checkIntruder() {
  // Measure distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * SOUND_SPEED / 2;
  Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");

  // Intruder detection
  if (distance > 0 && distance < DISTANCE_THRESHOLD) {
    Serial.println("🚨 Intruder detected!");
    
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    
    Blynk.virtualWrite(V0, 1);
    Blynk.virtualWrite(V1, 0);
    Blynk.logEvent("intruder_alert", "Intruder detected!");
    
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V1, 1);
  }
}