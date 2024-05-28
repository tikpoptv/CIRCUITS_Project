void BoardToBoard(){
  // ส่งคำร้องขอข้อมูลไปยัง ESP8266
  StaticJsonDocument<200> requestDoc;
  requestDoc["request"] = "data";
  requestDoc["IR_status"] = facestatus;
  String requestData;
  serializeJson(requestDoc, requestData);

  Serial2.println(requestData);
  Serial.println("Sent: " + requestData);

  // รอการตอบกลับจาก ESP8266
  unsigned long startTime = millis();
  while (!Serial2.available()) {
    if (millis() - startTime > 1000) { // Timeout หลังจาก 2 วินาที
      Serial.println("No response from ESP8266");
      digitalWrite(LED_PIN_SEND, HIGH); // กระพริบ LED ที่ D12
      delay(100);
      digitalWrite(LED_PIN_SEND, LOW);
      return;
    }
  }

  // อ่านการตอบกลับจาก ESP8266
  String received = Serial2.readString();
  Serial.println("Received: " + received);

  StaticJsonDocument<200> responseDoc;
  DeserializationError error = deserializeJson(responseDoc, received);

  // ตรวจสอบความถูกต้องของ JSON
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  humn = responseDoc["humn"];
  temp = responseDoc["temp"];
 // IR_status = responseDoc["IR_status"];
  value = responseDoc["value"];

  Serial.print("humn: ");
  Serial.println(humn);
  Serial.print("temp: ");
  Serial.println(temp);
  Serial.print("IR_status: ");
  Serial.println(IR_status);

  // ส่งข้อมูลยืนยันการรับกลับไปยัง ESP8266
  Serial2.println("ACK");
  Serial.println("Acknowledgment sent");

  digitalWrite(LED_PIN_RECEIVE, HIGH); // กระพริบ LED ที่ D14 เมื่อได้รับข้อมูลจาก ESP8266
  delay(100);
  digitalWrite(LED_PIN_RECEIVE, LOW);
}