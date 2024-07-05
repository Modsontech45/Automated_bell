#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;

int dayOfWeek, hour, minute, second;

bool sdCardInitialized = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // Ensure the LED is off initially

  // Attempt to initialize SD card
  if (SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD Card initialized.");
    sdCardInitialized = true;
    tmrpcm.speakerPin = 9;
    tmrpcm.setVolume(5);
  } else {
    Serial.println("SD Card initialization failed!");
    digitalWrite(LED_BUILTIN, HIGH); // Turn on LED if initialization fails
  }
}

void loop() {
  // Blink the LED to indicate the Arduino is ready to receive data
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);

  // Check if there is data available to read from serial
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    parseData(data);
    displayData();
  }
  
  if (sdCardInitialized) {
    
    if (dayOfWeek < 6 && hour == 7 && minute == 20 && second == 0) {
      play();
      tmrpcm.play("b1.wav");
     
    }
  }
}

void parseData(String data) {
  int commaIndex1 = data.indexOf(',');
  int commaIndex2 = data.indexOf(',', commaIndex1 + 1);
  int commaIndex3 = data.indexOf(',', commaIndex2 + 1);

  dayOfWeek = data.substring(0, commaIndex1).toInt();
  hour = data.substring(commaIndex1 + 1, commaIndex2).toInt();
  minute = data.substring(commaIndex2 + 1, commaIndex3).toInt();
  second = data.substring(commaIndex3 + 1).toInt();
}

void play() {
  tmrpcm.play("2.wav");
  delay(5000);
}

void displayData() {
  // Example of displaying parsed data
  Serial.print("Received data: ");
  Serial.print("Day: "); Serial.print(dayOfWeek);
  Serial.print(", Hour: "); Serial.print(hour);
  Serial.print(", Minute: "); Serial.print(minute);
  Serial.print(", Second: "); Serial.println(second);
}
