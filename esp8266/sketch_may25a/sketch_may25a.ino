#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial espSerial(D3, D4); // RX, TX

void setup() {
  espSerial.begin(9600); // เริ่มการสื่อสารที่ baud rate 9600
  Serial.begin(115200);
}

void loop() {
  BoardToBoard();
}
