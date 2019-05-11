#include "songs.h"
#include "wifi.h"

#include "secrets.h"

#define BAUD_RATE 9600
#define OUTPUT_PIN 6

#define VIRTUAL_KEYBOARD true

// https://github.com/256dpi/arduino-mqtt
#include <MQTT.h>
MQTTClient mqttClient;
unsigned long lastMillis = 0;

const int TIMER = 10000;
const char* mqttTopic = "nodemcu/signal";
const char* mqttTimerTopic = "nodemcu/timer";

void messageReceived(String &topic, String &payload) {
  Serial.println("Incoming MQTT message: " + topic + " - " + payload);
  
  if(VIRTUAL_KEYBOARD) {
    payload.toLowerCase();
    Serial.println("Sending payload...");
    Serial.println(payload);
    playSong(OUTPUT_PIN, payload);
  }
}

void connectMqtt() {
  Serial.println();
  Serial.print("Connecting to MQTT broker...\nClient Id:");
  Serial.println(mqttClientId);

  while (!mqttClient.connect(mqttClientId, mqttUsername, mqttPassword)) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("MQTT connected.");
  
  mqttClient.subscribe(mqttTopic);
//  mqttClient.unsubscribe(mqttTopic);

  mqttClient.onMessage(messageReceived);
}

void setup() {
  pinMode(6, OUTPUT); //Digital Pin 6 is where you connect your Buzzer
  Serial.begin(BAUD_RATE);
  
  if(VIRTUAL_KEYBOARD) {
    setupKeyboard();
    Serial.println("Welcome to the Virtual Keyboard!");
    Serial.println("Notes: S-D-F-G-H-J-K-L");
    Serial.println("  #  : -E-R---Y-U-I-");
    Serial.println();
  }

  setupWifiClient(ssid, pass);
//  testWifiConnection();
  
  // Initialize MQTT client
  mqttClient.begin(mqttBrokerHost, wifiClient);
  connectMqtt();

  // Publish a test mqtt event
  mqttClient.publish(mqttTopic, "sls");
}

void loop() {
  
  mqttClient.loop();
  delay(50);                                // for stability on ESP8266
  if (!mqttClient.connected()) {
    connectMqtt();
  }
  
  loopWifiClient();

  // publish a message roughly every ten second.
  if (millis() - lastMillis > TIMER) {
    lastMillis = millis();
    mqttClient.publish(mqttTimerTopic, TIMER / 1000);
  }
}
