BLYNK_WRITE(V2){
  
}

void BLYNK_send(){
  Blynk.virtualWrite(V5, humn);
  Blynk.virtualWrite(V6, temp);
}