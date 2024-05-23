
void get_Buzzer_Fc1(){

  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW);  
  delay(100);
  
}

void get_Buzzer_Fc2(){

   if(Buzzer_once == true){
      digitalWrite(Buzzer, HIGH);
      delay(100);
      digitalWrite(Buzzer, LOW);  
      delay(100);
      digitalWrite(Buzzer, HIGH);
      delay(100);
      digitalWrite(Buzzer, LOW);      
      Buzzer_once = false;
      Buzzer_Status = 0;
      Blynk.virtualWrite(V14, 0);
   }

}