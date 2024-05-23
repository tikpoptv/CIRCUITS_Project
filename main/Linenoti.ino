
//func send image
void sendLineNotify(){
      
     downloadAndSaveFile("/snapshot.jpg","http://"+ IPCAM_IP +"/out.jpg");
     LINE.notifyPicture("\n [อัตโนมัติ] \n ตรวจพบการเคลื่อนไหว \n \n ห้องหมายเลข : 18054 \n วันที่ : "+String(currentDate)+" \n เวลา : "+String(timeClient.getFormattedTime())+" ", SPIFFS, "/snapshot.jpg");  
     Serial.println("Send message");

  /*
  if(ipCameraEnabled){
     downloadAndSaveFile("/snapshot.jpg","http://"+ IPCAM_IP +"/out.jpg");
     LINE.notifyPicture("\n [อัตโนมัติ] \n ตรวจพบการเคลื่อนไหว \n \n ห้องหมายเลข : 18054  \n เวลา : "+String(timeClient.getFormattedTime())+" ", SPIFFS, "/snapshot.jpg");  
     Serial.println("Send message");
  } */
}
