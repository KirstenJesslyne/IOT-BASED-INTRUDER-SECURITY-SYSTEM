# IoT-Based Intruder Security System

An ESP32-based home security system using an ultrasonic sensor and the Blynk IoT platform. The system detects nearby motion, alerts with RGB LEDs and a buzzer, and sends real-time notifications via a mobile app.

## 📦 Hardware Used
- ESP32 DevKitC
- HC-SR04 Ultrasonic Sensor
- RGB LEDs (Red, Green, Blue)
- Buzzer (Active 5V)
- Jumper Wires
- Breadboard
- Micro USB Cable

## 🧠 Features
- Real-time motion detection within 50cm
- LED indicators: Green (safe), Red (intruder), Blue (Blynk status)
- Buzzer alerts on intrusion
- Control and monitor via Blynk (Virtual Pins)

## 🔌 Blynk Setup
- V0: Red LED (Intruder)
- V1: Green LED (System On)
- V2: Blue LED (Blynk Status)
- V5: Master On/Off Switch

## 🛠️ How to Run
1. Flash the code to the ESP32 using Arduino IDE
2. Connect to Wi-Fi by editing `ssid[]` and `pass[]` in the code
3. Use Blynk mobile app with the template info and virtual pins above
4. Power the ESP32 — system starts monitoring instantly

## 🚫 Limitations
- Only works if both ESP32 and phone are on the same Wi-Fi
- No camera or remote internet access
- Best suited for small indoor spaces

## 👥 Contributors
- Keira Azfiya ([LinkedIn](https://www.linkedin.com/in/keiraazfiya/))
- Kirsten Jesslyne ([LinkedIn](http://www.linkedin.com/in/kirstenjesslyne))
- Emeli Rahma Keren ([LinkedIn](https://www.linkedin.com/in/emelirahmakerenpurwadi))
- Kirana Diandri ([LinkedIn](https://id.linkedin.com/in/kiranadiandri))

## 📄 License
This project is for educational purposes only.
