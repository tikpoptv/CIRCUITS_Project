#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "tikxd_2G";
const char* password = "88888888";

String serverAddress = "http://192.168.2.34"; // URL ของเซิร์ฟเวอร์ PHP
String url = serverAddress + "/receive_data.php";
const int serverPort = 80; // พอร์ตของเซิร์ฟเวอร์ PHP

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected!");

  // สร้าง JSON สำหรับข้อมูลที่ต้องการส่ง
  String postData = "{\"sensor\":\"temperature\",\"value\":25.5}";

  // ส่งข้อมูล POST ไปยังเซิร์ฟเวอร์ PHP
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(postData);
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void loop() {
  // วงรอบหลัก
}
