#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <MFRC522.h>


#define DHTPIN 13
#define REED_PIN 16
#define motion 17
#define DHTTYPE DHT11
#define RST_PIN     22
#define SS_PIN      21 



MFRC522 mfrc522(SS_PIN, RST_PIN);
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "Home Network";
const char* password = "1234567890";


const char* mqttServer = "192.168.137.56";
const int mqttPort = 1883;
// const char* mqttUser = "";
// const char* mqttPassword = "";



String projectName = "esp1";
String pubtopic = projectName + "/data";
String subtopic = projectName + "/data";

WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msgString = "";
  for (int i = 0; i < length; i++) {
    msgString += (char)payload[i];
  }
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(msgString);
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(projectName.c_str())) {
      Serial.println("connected");
      client.subscribe(subtopic.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  dht.begin();
  pinMode(motion, INPUT);
  // pinMode(39, INPUT);
  SPI.begin();
  mfrc522.PCD_Init();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int proximity = digitalRead(REED_PIN);
  // int ldr = digitalRead(39);
  int val = digitalRead(motion);
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("UID tag :");
    String content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println(content);
    if(content==" 49 d0 a3 b2"){
      Serial.println("Authorized User");
      String payload="AuthorizeUser";
      client.publish("live/user", payload.c_str());
    }
    else{
      Serial.println("Unauthorized User");
      String payload="UnauthorizeUser";
      client.publish("live/user", payload.c_str());
    }
  }
  // if (isnan(h) || isnan(t)) {
  //   Serial.println(F("Failed to read from DHT sensor!"));
  //   return;
  // }
  // Serial.print(F("Humidity: "));
  // Serial.print(h);
  // Serial.print(F("%  Temperature: "));
  // Serial.print(t);
  // 	if (proximity == LOW) {
	// 	Serial.println("Door closed");
	// }
	// else {
	// 	Serial.println("Door opened");
	// }
  // Serial.println(val);
  //     if (val == HIGH) {
  //     Serial.println("Motion detected!"); 

  // } 
  // else {
  //       Serial.println("Motion stopped!");
  //   }
    int ldr = analogRead(36);
    // Serial.println(ldr);
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["temperature"] = t;
  jsonDoc["proximity"] = proximity;
  jsonDoc["motion"] = val;
  jsonDoc["humidity"] = h;
  jsonDoc["ldr"] = ldr;

  // Serialize the JSON object to a char array
  char jsonBuffer[200];
  serializeJson(jsonDoc, jsonBuffer);

  // Publish the JSON data to the MQTT client
  client.publish("test/updates", jsonBuffer);
    // client.publish("test/updates", "Hi I'm ESP32 ^^");
}


