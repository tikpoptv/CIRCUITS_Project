#include <Arduino.h>
#include <ArduinoJson.h>
#include <TridentTD_LineNotify.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

const char* ssid = "TIKXD";
const char* password = "22222222";
char auth[] = "iO2uFFq1MVVNy4ynsHdGLLJAox-5qmpe";

#define LINE_TOKEN "BttRigMYBnvIr2O17k6CYtv6rhA4pPrAiDHqAfkGQDg"


#define LED_PIN_SEND 12
#define LED_PIN_RECEIVE 14

int humn = 0;
int temp = 0;
int value = 0;

String FaceID;

int Buzzer = 22;

int facestatus = 0;


int IR_Home = 23;
int IR_status = 0;

int GAS_HOME = 13;
int IR_GAS = 0;


unsigned long previousMillis = 0;
const long interval = 2000; // 5 วินาที

void setup() {
  Serial.begin(115200); // เริ่มการสื่อสารที่ baud rate 115200 สำหรับ Serial Monitor
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // เริ่มการสื่อสารที่ baud rate 9600 สำหรับ Serial2 (TX = GPIO17, RX = GPIO16)

  pinMode(LED_PIN_SEND, OUTPUT);
  pinMode(LED_PIN_RECEIVE, OUTPUT);
  digitalWrite(LED_PIN_SEND, LOW);
  digitalWrite(LED_PIN_RECEIVE, LOW);


  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, LOW);

  connectWiFi();

  Blynk.begin(auth, ssid, password, "blynk.cloud", 80);
  Serial.println("เชื่อมต่อ Blynk สำเร็จ");

   LINE.setToken(LINE_TOKEN);
}


void loop() {
  BoardToBoard();

  BLYNK_send();

  updateLEDStatus("temp", String(temp)); 
  updateLEDStatus("humn", String(humn)); 

  Blynk.run();

  if(IR_status == 1){
    Serial.println("IR Status is 1"); // Debugging
    facestatus = 1;
  }

  IR_status = digitalRead(IR_Home); 

  IR_GAS = digitalRead(GAS_HOME); 

  Serial.println("IR_status: ");
  Serial.println(IR_status);

  Serial.println("GAS_HOME: ");
  Serial.println(IR_GAS);

  unsigned long currentMillis = millis();
  if (facestatus == 1) {
    String FaceID = checkFaceID();
    Serial.println("FaceID" + FaceID);
    if (FaceID == "Tik") {
      Serial.println("yes.");
      digitalWrite(Buzzer, HIGH);
      delay(100);
      digitalWrite(Buzzer, LOW);
      delay(100);
      digitalWrite(Buzzer, HIGH);
      delay(100);
      digitalWrite(Buzzer, LOW);
      facestatus = 0;
      previousMillis = currentMillis; // รีเซ็ตเวลา
    } else {
      if (currentMillis - previousMillis >= interval) {
        Serial.println("พบผู้บุกรุก.");
        digitalWrite(Buzzer, HIGH);
        previousMillis = currentMillis; // รีเซ็ตเวลาเพื่อนับใหม่
      }
    }
  }

  if(IR_GAS == 1){
    LINE.notify("\n [อัตโนมัติ] \n พบการรั่วไหลของแก๊ส ");
    digitalWrite(Buzzer, HIGH);
    delay(500);
    digitalWrite(Buzzer, LOW);
    delay(100);
  }
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

String checkFaceID() {
  HTTPClient http;
  
  // สร้าง URL สำหรับร้องขอสถานะ LED โดยใช้ชื่อ
  String url = "http://172.20.10.2:5000/";
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
