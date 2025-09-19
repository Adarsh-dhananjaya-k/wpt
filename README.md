# WPT_ELECTROINC_WORKSHOP  

## 🔌 ESP8266 Pinout & Explanation  

The **ESP8266** is a low-cost Wi-Fi microchip with full TCP/IP stack and microcontroller capability. It is widely used in **IoT projects**, **smart devices**, and **wireless automation**.  

### 📍 Pinout Diagram (NodeMCU ESP8266 Example)  
<img width="1238" height="1141" alt="image" src="https://github.com/user-attachments/assets/115e7ede-e98c-4477-8f01-00f78a711692" />

| Pin Name | GPIO No. | Function | Notes |
|----------|----------|----------|-------|
| D0       | GPIO16   | Digital I/O | No PWM, no interrupts |
| D1       | GPIO5    | Digital I/O, I2C (SCL) | Can be used for I2C |
| D2       | GPIO4    | Digital I/O, I2C (SDA) | Can be used for I2C |
| D3       | GPIO0    | Digital I/O | Pull-up needed at boot |
| D4       | GPIO2    | Digital I/O, Built-in LED | Pull-up at boot |
| D5       | GPIO14   | Digital I/O, SCLK | Commonly used for SPI |
| D6       | GPIO12   | Digital I/O, MISO | Commonly used for SPI |
| D7       | GPIO13   | Digital I/O, MOSI | Commonly used for SPI |
| D8       | GPIO15   | Digital I/O, CS | Pull-down at boot |
| RX       | GPIO3    | UART RX | Serial communication |
| TX       | GPIO1    | UART TX | Serial communication |
| A0       | Analog 0 | ADC (0–1V input) | Only **one analog pin** |
| GND      | –        | Ground | Connect to GND |
| 3V3      | –        | Power (3.3V) | Do NOT use 5V directly |
| VIN      | –        | Power Input (5V) | Onboard regulator to 3.3V |

---

### ⚡ Key Notes
- **Operating Voltage**: 3.3V (⚠️ do not supply 5V directly to pins).  
- **Digital Pins**: Most GPIOs support **PWM, I2C, SPI, UART**.  
- **Boot Restrictions**: GPIO0, GPIO2, and GPIO15 affect boot mode (must be pulled high/low accordingly).  
- **Analog Pin**: Only **1 analog input (A0)** with a 10-bit resolution (0–1023).  
- **Flash & Reset**: Some pins are reserved internally, so not all GPIOs are free for general use.  

---

## 📱 Blynk Software  

**Blynk** is a platform that allows you to **control hardware remotely**, display sensor data, and create IoT applications using a **smartphone app** and the **Blynk cloud/server**.  

It is especially popular for projects with **ESP8266, ESP32, Arduino, and Raspberry Pi**.  

### 🔑 Features  
- 📲 **Mobile App (iOS/Android)** – Drag-and-drop interface to design dashboards (buttons, sliders, graphs, etc.).  
- ☁️ **Blynk Cloud** – Free cloud service to connect your devices without building your own server.  
- 🖥 **Blynk Console (Web Dashboard)** – Monitor & control devices from your computer browser.  
- 🔌 **Supports Multiple Boards** – Arduino, ESP8266, ESP32, Raspberry Pi, etc.  
- 🔔 **Notifications & Automations** – Send alerts, trigger events, and schedule tasks.  

<img width="1407" height="766" alt="image" src="https://github.com/user-attachments/assets/87f43e9d-5c90-41b6-a2a3-1458b56c3710" />

---

## 🛠 Workshop Project List  

This workshop includes **hands-on IoT projects** using ESP8266, sensors, and Blynk/Cloud platforms.  

### 1. 🚗 IoT-Based Smart Car Parking System  
- Uses IR sensors and a **Blynk dashboard** to detect and display parking slot availability.  
- **Code**: [IoT_Car_Parking_System.ino](https://github.com/Adarsh-dhananjaya-k/WPT_ELECTROINC_WORKSHOP/blob/main/IoT_Car_Parking_System.ino)  

### 2. 🌱 Smart Irrigation System  
- Automates irrigation using a soil moisture sensor + relay.  
- Pump status updates live on **Blynk platform**.  
- **Code**: [smart_irrigation_system.ino](https://github.com/Adarsh-dhananjaya-k/WPT_ELECTROINC_WORKSHOP/blob/main/smart_irrigation_system.ino)  

### 3. 🏠 Alexa-Based Home Automation System  
- Control appliances with **Alexa voice commands** via Arduino Cloud / Prosoince.  
- **Code**: [google_internet_Things.ino](https://github.com/Adarsh-dhananjaya-k/WPT_ELECTROINC_WORKSHOP/blob/main/google_internet_Things.ino)  

### 4. 💧 IoT-Based Water Level Indicator  
- Uses **Ultrasonic Sensor (HC-SR04)** + ESP8266/ESP32.  
- Displays water level % on a **web server**.  
- **Code**: [esp32_web_server.ino](https://github.com/Adarsh-dhananjaya-k/WPT_ELECTROINC_WORKSHOP/blob/main/esp32_web_server.ino)  

---

## ⚙️ Setup Instructions  

1. Clone this repository:  
   ```bash
   git clone https://github.com/Adarsh-dhananjaya-k/WPT_ELECTROINC_WORKSHOP.git
   cd WPT_ELECTROINC_WORKSHOP
```
