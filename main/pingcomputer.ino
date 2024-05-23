void ping(){

  unsigned long currentTime = millis();
  
  // Check if it's time to ping
  if (currentTime - lastPingTime >= pingInterval) {
    lastPingTime = currentTime; // Update last ping time

    pinger.Ping(IPAddress(192, 168, 2, 39));

    pinger.OnReceive([](const PingerResponse& response) {
      if (response.ReceivedResponse) {
        Serial.println("response.ReceivedResponse เชื่อมต่อแล้ว");
      } else {
        Serial.println("response.ReceivedResponse เชื่อมต่อล้มเหลว");
      }
      return false; // Stop ping sequence after the first response
    });

    // Perform ping
    
  }
}