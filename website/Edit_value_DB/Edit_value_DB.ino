#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "tikxd_2G";
const char* password = "88888888";

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  updateLEDStatus("Led4", "ON"); // ตัวอย่างการเรียกฟังก์ชันอัปเดตสถานะ LED
}

void loop() {
  // คุณสามารถเพิ่มโค้ดอื่นๆ ที่ต้องการให้ ESP32 ทำต่อไปในลูปนี้
}

void updateLEDStatus(String name, String status) {
  HTTPClient http;

  String serverAddress = "http://192.168.2.34/control.php"; // ใส่ที่อยู่ URL ของไฟล์ PHP ที่ใช้ในการอัปเดต LED
  String postData = "name=" + name + "&status=" + status;

  http.begin(serverAddress);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Response: " + response);
  } else {
    Serial.print("Error occurred: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
