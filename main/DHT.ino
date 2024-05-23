/* function DHT */
void get_dht(){
  //read dht
  humn = dht.readHumidity();
  temp = dht.readTemperature();
  //chk dht
  if(isnan(humn) || isnan(temp)){
    Serial.println("DHT ERROR");
   // digitalWrite(led_alert_DHT, LOW);
    LED_DHT22_ONLINE.off();
    LED_DHT22_OFFLINE.on();
    humn = 0;
    temp = 0;
    //delay(1500);
    //return;
  }
  else{
    Serial.print("HUM : ");
    Serial.print(humn);
    Serial.println(" %");
    Serial.println("");
    Serial.print("Temp : ");
    Serial.print(temp);
    Serial.println(" C");

   // digitalWrite(led_alert_DHT, HIGH);
    LED_DHT22_ONLINE.on();
    LED_DHT22_OFFLINE.off();
    
  }
  Blynk.virtualWrite(V5, humn);
  Blynk.virtualWrite(V6, temp);
}


void get_DHT_LineNotify(){
  if(temp < 30){ //ถ้าอุณหภูมิมากกว่า 26 ให้ทำอะไร
    send_notify = true;
    LINE.notify("อัตโนมัติ \n มีโอกาสที่ห้องไม่ได้ปิดแอร์ \n อุณหภูมิตอนนี้ :  "+String(temp)+" C \n เวลา : "+String(timeClient.getFormattedTime())+"");
    delay(300000);
  }
  else{
    if(send_notify == true){
      LINE.notify("อัตโนมัติ \n ห้องอุณหภูมิปกติ \n อุณหภูมิตอนนี้ : "+String(temp)+" C \n เวลา : "+String(timeClient.getFormattedTime())+"");
      send_notify = false;
    }
  }
}
