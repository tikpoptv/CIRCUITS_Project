#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "tikxd_2G";
const char* password = "88888888";

void setup() {
  Serial.begin(115200);

  // เชื่อมต่อ WiFi
  connectWiFi();

  // เรียกใช้งานฟังก์ชันเช็คสถานะ LED โดยระบุชื่อ "Led1"
  String ledStatus = checkLEDStatus("Led1");
  Serial.println("LED1 status: " + ledStatus);
}

void loop() {
  // ไม่มีการทำงานใน loop() ในตัวอย่างนี้
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to WiFi");
}

String checkLEDStatus(String name) {
  HTTPClient http;
  
  // สร้าง URL สำหรับร้องขอสถานะ LED โดยใช้ชื่อ
  String url = "http://192.168.2.34/check_led_status.php?name=" + name;
  http.begin(url);

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    return http.getString(); // คืนค่าสถานะ LED ที่ได้รับจากเซิร์ฟเวอร์
  } else {
    Serial.print("Error occurred: ");
    Serial.println(httpResponseCode);
    return "Error";
  }

  http.end();
}
