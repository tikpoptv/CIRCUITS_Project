#include <TridentTD_LineNotify.h>
#include <FS.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>

/* include : time */
#include <NTPClient.h>
#include <WiFiUdp.h>


///////////////////////////////////
#include <Pinger.h>
#include <lwip/icmp.h> // needed for icmp packet definitions


const unsigned long pingInterval = 3000; // Ping interval in milliseconds

// IP address to ping
IPAddress pingAddr(192, 168, 2, 39);

unsigned long lastPingTime = 0;
Pinger pinger;


///////////// wake on land /////////////////////////
#include <WakeOnLan.h>

WiFiUDP UDP;
WakeOnLan WOL(UDP);
////////////////////////////////////////////////////
//rfid
#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above

// MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
// MFRC522::MIFARE_Key key;
// String tag;
//sensor DHT
#include <DHT.h>               
#define DHTPIN  D2              
#define DHTTYPE DHT22      
DHT dht(DHTPIN, DHTTYPE);   
WidgetLED LED_DHT22_ONLINE(V7);
WidgetLED LED_DHT22_OFFLINE(V8);
float humn; //humidity
float temp; //temperature
//sensor PIR
int PIR = D1;
int pir_val = 0;
int pir_on = 0;
WidgetLCD LCD(V0); 
WidgetLED LED_PIR(V1); // LED การเคลื่อนไหว
WidgetLED LED_PIR_ONLINE(V3);
WidgetLED LED_PIR_OFFLINE(V4);
float PIR_Read;

//BUZZER
int Buzzer = D8;

//line not
#define TOKENCOUNT  1  //How many token that you want to send? (Size of array below)
#define LINE_TOKEN "BttRigMYBnvIr2O17k6CYtv6rhA4pPrAiDHqAfkGQDg"
int send_once = 0;

String IPCAM_IP  =  "172.20.10.7:8888";
bool ipCameraEnabled = true; 

//blynk
#define BLYNK_PRINT Serial
#define BLYNK_AUTH_TOKEN "DyflnmKxcEFHX3YF5YN1orJVrnTB_5EK" //Enter your blynk auth token
bool Connected2Blynk = false;
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "TIKXD";
char pass[] = "22222222";
BlynkTimer timer;

//pin
//int led_alert_DHT = D4;
int led_alert_PIR = D0;



//send notify
bool send_notify = true;

//pir_on_once
bool pir_on_once = true;

//Buzzer_once
bool Buzzer_once = true;

//delay
int delay_loop = 1000;

/* time */
const long offsetTime = 25200;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200 );
int hourNow, minuteNow, secondNow;

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
 
//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
String currentDate;

// TIME CONTROL
// DHT //
const int DHT_START_hour = 1;
const int DHT_START_minute = 56;

// PIR //
const int PIR_START_hour = 17;
const int PIR_START_minute = 30;
const int PIR_END_hour = 5;
const int PIR_END_minute = 30;
//
const int PIR_START_hour_PM = PIR_START_hour;
const int PIR_START_hour_AM = PIR_END_hour - 1;
//
int Automatic_PIR_Status = 0; 
int Automatic_PIR = 0;
int PIR_Close = 0;
int PIR_Button = 0;


//Buzzer 

int Buzzer_Button = 0;
int Buzzer_Status = 0;



//esp to esp
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial espSerial(D3, D4); // RX, TX



/////////


///IR Home


int IR_status = 0;



////

void setup() { //Start Setup

  espSerial.begin(9600); // เริ่มการสื่อสารที่ baud rate 9600
  //Serial port
  Serial.begin(115200);

  //connect internet
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  

  //line not
  LINE.setToken(LINE_TOKEN);

  //camera setup
  chk_camera();

  //dht
  dht.begin();
  //timer.setInterval(2500, Sensor);

  //pir
  pinMode(PIR, INPUT);

  //Buzzer 
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, LOW);

  //pin setup
 // pinMode(led_alert_DHT, OUTPUT);
 // digitalWrite(led_alert_DHT, LOW);

  pinMode(led_alert_PIR, OUTPUT);
  digitalWrite(led_alert_PIR, LOW);

  //time
  timeClient.begin();
  timeClient.update();

  // ///// rfid
  // SPI.begin(); // Init SPI bus
  // rfid.PCD_Init(); // Init MFRC522
  

  //Blynk
  Blynk.virtualWrite(V10, 0);


  
  

  ////////////////////////////// wake on lan
  WOL.setRepeat(3, 100);
  WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask()); // Optional  => To calculate the broadcast address, otherwise 255.255.255.255 is used (which is denied in some networks).
  wakeMyPC();
  /////////////////////////////
} //END Setup



void loop() { //Start loop


  ////////////////////////////////////////////////////////////////
  /* read sensor and start blynk*/
  get_dht();   //read humidity and temperature
  Read_IR();

  BoardToBoard();


 // get_pir();   //motion sensor
  Blynk.run(); //start blynk 
  ////////////////////////////////////////////////////////////////
 // ping();


  ////////////////////////////////////////////////////////////////

  if (Buzzer_Status == 1) {
      get_Buzzer_Fc1();
  } 
  else if(Buzzer_Status == 2) {
      Buzzer_once = true;
      get_Buzzer_Fc2();
  }
  

  ////////////////////////////////////////////////////////////////


  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  if(timeClient.isTimeSet()) {
    if (DHT_START_hour == timeClient.getHours() && DHT_START_minute <= timeClient.getMinutes()) {
        get_DHT_LineNotify();
    } 
  }


  //////////////////////////////////////////////////////////////////
    if (Automatic_PIR_Status == 1) {
      Serial.println("Automatic_PIR_Status = 1");   
      Automatic_PIR = 1;    
    }
    else {
        Automatic_PIR = 0; 
    }      


    if(PIR_Close == 1){
      pir_on = 0;
      PIR_Button = 0;
      Blynk.virtualWrite(V2, 0);
      Serial.println("ระบบอัตโนมัติโดนบังคับปิด");
    }
    else {
      get_Automatic_PIR();
      if(PIR_Button == 1){
        pir_on = 1;
      }
      else {
        pir_on = 0;
      }
      if(Automatic_PIR == 1){    
        pir_on = 1;
        Blynk.virtualWrite(V2, 0);
        Serial.println("ระบบอัตโนมัติกำลังทำงานตามเวลาที่กำหนด");
        pir_on_once = true;
      } 
      else {
        if(pir_on_once == true){
          pir_on = 0;
          pir_on_once = false;
        }
      }
    }

    ////
//Get a time structure

    /////
 unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
   
  struct tm *ptm = gmtime ((time_t *)&epochTime); 
 
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  String currentMonthName = months[currentMonth-1];
  int currentYear = ptm->tm_year+1900;
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  Serial.print("Current date: ");
  Serial.println(currentDate);

  ///////////////////////
  /* delay */ 
//  delay(delay_loop);
} //END LOOP

