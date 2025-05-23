# Smart Water Quality Analysis System

An IoT-based solution that monitors the real-time quality of water using pH, TDS, and temperature sensors. The data is displayed on an LCD and transmitted wirelessly using ESP32 to a Firebase Realtime Database for remote monitoring and analytics.

---

## Objectives

- Monitor essential water quality parameters (pH, TDS, temperature).
- Display data in real-time on an LCD.
- Store and visualize live data on the Firebase cloud platform.
- Enable scalable, low-cost, and portable water quality monitoring.

---

## Components Used

- ESP8266 / NodeMCU (Microcontroller)
- pH Sensor Probe
- TDS Sensor
- Temperature Sensor (DS18B20 or similar)
- 16x2 LCD Display with I2C module
- Firebase Realtime Database
- Jumper Wires, Breadboard, USB Cable

---

## Cloud Integration (Firebase)

1. Set up a Firebase project from [firebase.google.com](https://firebase.google.com/)
2. Copy the Database URL and Web API Key.
3. Add the Firebase library for ESP32 to the Arduino IDE.
4. Connect ESP32 via USB and upload the code with Wi-Fi + Firebase credentials.

---

## How to Run

1. Clone this repository.
2. Open `IDE_Code/Code_File_Iot.ino` in Arduino IDE.
3. Modify with your Wi-Fi and Firebase credentials.
4. Upload to ESP32.
5. Observe readings on the LCD and Firebase dashboard.

---

## Results

- LCD Display output
- Realtime Firebase database updates
- IDE Serial Monitor output

---

## Future Enhancements

- Add more sensors (e.g., turbidity, dissolved oxygen).
- SMS/Email alerts for unsafe water quality.
- Android/iOS App for visualization.

---

## Team Members

- Palak Bedi (22070521004)
- Manya Asrani (22070521042)
- Swarali Limaye (22070521144)

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.



