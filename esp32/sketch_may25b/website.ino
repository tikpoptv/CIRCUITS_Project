void updateLEDStatus(String name, String status) {
  HTTPClient http;

  String serverAddress = "http://172.20.10.2/web/control.php"; // ใส่ที่อยู่ URL ของไฟล์ PHP ที่ใช้ในการอัปเดต LED
  String postData = "name=" + name + "&status=" + status;

  http.begin(serverAddress);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    String response = http.getString();
   // Serial.println("Response: " + response);
  } else {
    Serial.print("Error occurred: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
