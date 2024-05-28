void BoardToBoard(){
  // รอรับข้อมูลจาก ESP32
  unsigned long startTime = millis();
  while (!espSerial.available()) {
    if (millis() - startTime > 2000) { // Timeout หลังจาก 2 วินาที
      Serial.println("No response from ESP32");
      return;
    }
  }

  // อ่านข้อมูลจาก ESP32
  String received = espSerial.readString();
  Serial.println("Received from ESP32: " + received);

  StaticJsonDocument<200> requestDoc;
  DeserializationError error = deserializeJson(requestDoc, received);

  IR_status = requestDoc["IR_status"];

  Serial.print("IR_status: ");
  Serial.println(IR_status);
  
  // ตรวจสอบความถูกต้องของ JSON
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  // สร้าง JSON response
  StaticJsonDocument<200> responseDoc;
  responseDoc["humn"] = humn;
  responseDoc["temp"] = temp;
  responseDoc["IR_status"] = IR_status; // สร้างค่าสุ่มสำหรับอุณหภูมิ

  String response;
  serializeJson(responseDoc, response);

  // ส่งข้อมูลตอบกลับไปยัง ESP32
  espSerial.println(response);
  Serial.println("Sent: " + response);
  digitalWrite(led_alert_PIR, HIGH);
  delay(100);
  digitalWrite(led_alert_PIR, LOW);

  // รอการตอบกลับจาก ESP32
  startTime = millis();
  while (!espSerial.available()) {
    if (millis() - startTime > 2000) { // Timeout หลังจาก 2 วินาที
      Serial.println("No acknowledgment from ESP32");
      return;
    }
  }

  // อ่านการตอบกลับจาก ESP32
  String ackReceived = espSerial.readString();
  Serial.println("Received acknowledgment from ESP32: " + ackReceived);
}
