#include <WiFi.h>
#include <PubSubClient.h>
#include <map> 
#include <vector>
#include <string> 


std :: vector<int> pins={16,22,4,3,21,19,18,5};
// #define LED_PIN1 23
// #define LED_PIN2 22
// #define LED_PIN3 1
// #define LED_PIN4 3
// #define LED_PIN5 21
// #define LED_PIN6 19
// #define LED_PIN7 18
// #define LED_PIN8 5
const int freq = 5000;
const int ledChannel = 0;
const int ledChannel2 = 1;
const int resolution = 8;
const int ledPin = 16; 
const int ledPin2 = 22; 

const char* ssid = "Home Network";
const char* password = "1234567890";
const char* mqttServer = "192.168.137.56";
const int mqttPort = 1883;
WiFiClient espClient;
PubSubClient client(espClient);
String projectName = "smarthome";
String subtopic = projectName + "/control";
String ldrtopic = "live/ldr";
String dimmertopic = "live/dimmer";
void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


bool entryModeActive = false;
bool sleepModeActive = false;

// void entryMode() {
//   // Turn on all LEDs
//   turnOffSleepMode();
// for (int i = 0; i < 4; i++) {
//   delay(200);
//     char buffer[10]; // Make sure it's large enough to hold the string representation of the integer
//     itoa(i + 1, buffer, 10); // Convert integer to string
//     const char* temp = "on";
//     const char* charValue = buffer;
    
//     // Construct the payload as a String
//     String payload = temp;
//     payload += charValue;

//     // Convert the payload String to a C-style string (const char*) using c_str() method
//     client.publish("smarthome/control", payload.c_str());

//     // Set the pin to HIGH
//     digitalWrite(pins[i], HIGH);
// }
//   // entryModeActive = true;
//   // sleepModeActive = false;
// }

// void sleepMode() {
//   // Turn off all LEDs
  
//   for (int i = 0; i < pins.size()-2; i++) {

//     delay(200);
//             char buffer[10]; // Make sure it's large enough to hold the string representation of the integer
//     itoa(i + 1, buffer, 10);
//         const char* temp = "off";
//     const char* charValue = buffer;
    
//     // Construct the payload as a String
//     String payload = temp;
//     payload += charValue;

//     // Convert the payload String to a C-style string (const char*) using c_str() method
//     client.publish("smarthome/control", payload.c_str());
//     if(i!=4)
//       digitalWrite(pins[i], LOW);
//   }
//   for (int i =6; i < pins.size(); i++) {
//     delay(200);
//         char buffer[10]; // Make sure it's large enough to hold the string representation of the integer
//     itoa(i + 1, buffer, 10);
//         const char* temp = "on";
//     const char* charValue = buffer;
    
//     // Construct the payload as a String
//     String payload = temp;
//     payload += charValue;

//     // Convert the payload String to a C-style string (const char*) using c_str() method
//     client.publish("smarthome/control", payload.c_str());
//     digitalWrite(pins[i],HIGH );
//   }
//   // entryModeActive = false;
//   // sleepModeActive = true;
// }

// void turnOffEntryMode() {
//   // Turn off entry mode
//   // entryModeActive = false;
//   // Implement logic to turn off entry mode if needed
//   for (int i = 0; i < pins.size(); i++) {
//     digitalWrite(pins[i], LOW);
//   }
// }

// void turnOffSleepMode() {
//   // Turn off sleep mode
//   // sleepModeActive = false;
//   // Implement logic to turn off sleep mode if needed
//   for (int i = 6; i < pins.size(); i++) {
//     digitalWrite(pins[i], LOW);
//   }
//   digitalWrite(pins[1],HIGH);
// }


void entryMode()
{
  // turnoffsleepmode();
    String payload = "off7";
  client.publish("smarthome/feedback", payload.c_str());
    digitalWrite(pins[6], LOW);
    payload = "off8";
  client.publish("smarthome/feedback", payload.c_str());
   digitalWrite(pins[7], LOW);
  for(int i=1;i<4;i++)
  {
    delay(200);
    char buffer[10]; // Make sure it's large enough to hold the string representation of the integer
    itoa(i + 1, buffer, 10);
        const char* temp = "on";
    const char* charValue = buffer;
    
    // Construct the payload as a String
    String payload = temp;
    payload += charValue;

    // Convert the payload String to a C-style string (const char*) using c_str() method
    client.publish("smarthome/feedback", payload.c_str());
    digitalWrite(pins[i], HIGH);
  }
}
void turnoffentrymode()
{
  for(int i=1;i<8;i++)
  {
        delay(200);
    char buffer[10]; // Make sure it's large enough to hold the string representation of the integer
    itoa(i + 1, buffer, 10);
        const char* temp = "off";
    const char* charValue = buffer;
    
    // Construct the payload as a String
    String payload = temp;
    payload += charValue;

    // Convert the payload String to a C-style string (const char*) using c_str() method
    client.publish("smarthome/feedback", payload.c_str());
    digitalWrite(pins[i], LOW);
  }
}
void sleepMode()
{
  for(int i=1;i<4;i++)
  {
    delay(200);
        char buffer[10]; // Make sure it's large enough to hold the string representation of the integer
    itoa(i + 1, buffer, 10);
        const char* temp = "off";
    const char* charValue = buffer;
    
    // Construct the payload as a String
    String payload = temp;
    payload += charValue;

    // Convert the payload String to a C-style string (const char*) using c_str() method
    client.publish("smarthome/feedback", payload.c_str());
    digitalWrite(pins[i], LOW);
  }
  String payload = "on7";
  client.publish("smarthome/feedback", payload.c_str());
   digitalWrite(pins[6], HIGH);
   delay(200);
  payload = "on8";
  client.publish("smarthome/feedback", payload.c_str());
   digitalWrite(pins[7], HIGH);
}
void turnoffsleepmode()
{
    String payload = "off7";
  client.publish("smarthome/feedback", payload.c_str());
  digitalWrite(pins[6], LOW);
     delay(200);
    payload = "off8";
  client.publish("smarthome/feedback", payload.c_str());
   digitalWrite(pins[7], LOW);
}

void reconnect() {
   Serial.print(mqttServer);
    Serial.print(":");
    Serial.print(mqttPort);
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(projectName.c_str())) {
      Serial.println("connected");
      client.subscribe(subtopic.c_str());
      client.subscribe(ldrtopic.c_str());
      client.subscribe(dimmertopic.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length) {
  // Handle MQTT messages here if needed
  String msgString = "";
  for (int i = 0; i < length; i++) {
    msgString += (char)payload[i];
  }
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(msgString);
 if(strcmp(topic, ldrtopic.c_str()) == 0) {
    int intValue = atoi(msgString.c_str());
    
    // Map the light intensity to the duty cycle range 0-255 (inverse mapping)
    int dutyCycle = map(intValue, 0, 100, 255, 0);

    // Set the PWM duty cycle for LED brightness
    ledcWrite(ledChannel, dutyCycle);

    // // Print the light percentage and duty cycle
    // Serial.print("Light Percentage: ");
    // Serial.print(intValue);
    // Serial.print("%, Duty Cycle: ");
    // Serial.println(dutyCycle);
}
else if(strcmp(topic, dimmertopic.c_str()) == 0){
      int intValue = atoi(msgString.c_str());
    
    // Map the light intensity to the duty cycle range 0-255 (inverse mapping)
    int dutyCycle = map(intValue, 0, 100, 0, 255);

    // Set the PWM duty cycle for LED brightness
    ledcWrite(ledChannel2, dutyCycle);

    // Print the light percentage and duty cycle
    Serial.print("Slider: ");
    Serial.print(intValue);
    Serial.print("%, : ");
    Serial.println(dutyCycle);

}
    int req_pin;
  if(msgString.startsWith("on")){
    String temp=msgString.substring(2);
    req_pin = temp.toInt()-1;
    if(req_pin!=0)
    {
    digitalWrite(pins[req_pin], HIGH);

    }
    // Serial.println("Switching LED"1 ON");
  }
  else if(msgString.startsWith("off")){
    String temp=msgString.substring(3);
    req_pin = temp.toInt()-1;
        if(req_pin!=0)
    {
    digitalWrite(pins[req_pin], LOW);

    }
  }

    if (strcmp(topic, subtopic.c_str()) == 0) {
    if (msgString.equals("entry_mode_on")) {
      client.publish("live/currentmode", "Entry Mode");
      if (!entryModeActive) {
        entryMode();
        // turnOffSleepMode();
      }
    } 
    // else if (msgString.equals("entry_mode_off")) {
    //   if (entryModeActive) {
    //     turnOffEntryMode();
    //   }
    // } 
    else if (msgString.equals("sleep_mode_on")) {
      client.publish("live/currentmode","Sleep Mode");
      if (!sleepModeActive) {
        sleepMode();
        // turnOffEntryMode();
      }
     }
         else if (msgString.equals("entry_mode_off")) {
      // client.publish("live/currentmode","Sleep Mode");

        turnoffentrymode();
        // turnOffEntryMode();
     }
    // else if (msgString.equals("sleep_mode_off")) {
    //   if (sleepModeActive) {
    //     turnOffSleepMode();
    //   }
    // }
  }

}



void setup() {
  Serial.begin(115200);
    client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  connectToWiFi();
  // pinMode(LED_PIN1, OUTPUT);
  // pinMode(LED_PIN2, OUTPUT);
  // pinMode(LED_PIN3, OUTPUT);
  // pinMode(LED_PIN4, OUTPUT);
  // pinMode(LED_PIN5, OUTPUT);
  // pinMode(LED_PIN6, OUTPUT);
  // pinMode(LED_PIN7, OUTPUT);
  // pinMode(LED_PIN8, OUTPUT);
  for(int i=1;i<pins.size();i++){
    pinMode(pins[i],OUTPUT);
  }
    // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
      // configure LED PWM functionalitites
  ledcSetup(ledChannel2, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin2, ledChannel2);

}

void loop() {
  // Your code here
    if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
