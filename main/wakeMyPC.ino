
void wakeMyPC() {
    const char *MACAddress = "B4:2E:99:EE:43:3F";
  
    WOL.sendMagicPacket(MACAddress); // Send Wake On Lan packet with the above MAC address. Default to port 9.
    // WOL.sendMagicPacket(MACAddress, 7); // Change the port number
}