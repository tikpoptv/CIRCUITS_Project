# Motion Detection and Environment Monitoring System

## Introduction
Welcome to the Motion Detection and Environment Monitoring System! This project serves as a practical application within the BASIC CIRCUITS AND ELECTRONICS course, aimed at providing hands-on experience in designing and implementing electronic circuits. 

The system employs an ESP8266 microcontroller board along with various sensors to detect motion and monitor environmental conditions such as temperature and humidity. Through the integration of Blynk and LINE Notify, it offers real-time data visualization and notification capabilities.

## Features
- **Motion Detection:** Utilizes a Passive Infrared Sensor (PIR) to detect motion within the monitored area.
- **Temperature and Humidity Monitoring:** Utilizes a DHT22 sensor to measure temperature and humidity levels.
- **Real-time Data Visualization:** Provides live visualization of temperature and humidity data through the Blynk application.
- **Remote Notifications:** Sends notifications via LINE Notify when motion is detected or environmental conditions exceed predefined thresholds.

## Installation
1. Clone or download this repository to your local machine.
2. Open the `main.ino` file in the Arduino IDE.
3. Customize the WiFi credentials and Blynk Auth Token with your own information.
4. Upload the code to your ESP8266 board.
5. Connect the necessary sensors according to the wiring diagram provided.

## Usage
1. Power up the system and ensure it is connected to the internet.
2. Open the Blynk application on your smartphone and monitor the real-time temperature and humidity data.
3. Receive LINE notifications when motion is detected or environmental conditions require attention.

## Course Information
This project is developed as part of the BASIC CIRCUITS AND ELECTRONICS course, which focuses on introducing fundamental electronic concepts and practical circuit design techniques. Through hands-on projects like this, students gain valuable experience in applying theoretical knowledge to real-world applications.
