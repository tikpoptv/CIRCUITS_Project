
//////////////////////////////////////////////////////////////////
//button pir
BLYNK_WRITE(V2){
  if(param.asInt()){
      PIR_Button = 1;
      
  }
  else{
      PIR_Button = 0;
  }
}
//////////////////////////////////////////////////////////////////
BLYNK_WRITE(V10){
  if(param.asInt()){
    Blynk.virtualWrite(V11, "ระบบอัตโนมัติโดนบังคับปิด");
    PIR_Close = 1;
  }
  else{
     PIR_Close = 0;
     Blynk.virtualWrite(V11, "ระบบอัตโนมัติทำงานโดยอัตโนมัติ");
     Serial.println("ระบบอัตโนมัติทำงานโดยอัตโนมัติ");
     send_notify = true;
  }
}


BLYNK_WRITE(V9){
  if(param.asInt()){
    Serial.println("BUZZER TEST!!!!");
    digitalWrite(Buzzer, HIGH);
  }
  else{
    digitalWrite(Buzzer, LOW);
    
  }
}

BLYNK_WRITE(V12){
  if(param.asInt()){
    Buzzer_Button = 1;
  }
  else{
    Buzzer_Button = 0;
    Buzzer_Status = 0;
  }
}

BLYNK_WRITE(V13){
  if(param.asInt()){
    Buzzer_Status = 1;
  }
  else{
    Buzzer_Status = 0;
  }
}

BLYNK_WRITE(V14){
  if(param.asInt()){
    Buzzer_Status = 2;
  }
  else{
    Buzzer_Status = 0;
  }
}

