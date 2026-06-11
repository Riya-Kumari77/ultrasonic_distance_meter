# Wi-Fi Controlled Ultrasonic Distance Meter Robot

A Wi-Fi-controlled robot built using the Seeed Studio XIAO ESP32-C6, HC-SR04 Ultrasonic Sensor, and L298N Motor Driver. The robot creates its own Wi-Fi hotspot, allowing users to control movement and monitor real-time distance measurements directly from a smartphone browser.

---

## Features

* Real-time distance measurement using HC-SR04
* Distance displayed on Serial Monitor
* Distance displayed on a mobile web dashboard
* Wi-Fi Access Point mode (no router required)
* Smartphone-based robot control
* Forward movement
* Backward movement
* Left turn
* Right turn
* Emergency stop
* Simple and responsive web interface

---

## Hardware Requirements

| Component                 | Quantity    |
| ------------------------- | ----------- |
| XIAO ESP32-C6             | 1           |
| HC-SR04 Ultrasonic Sensor | 1           |
| L298N Motor Driver        | 1           |
| DC Gear Motors            | 2           |
| Robot Chassis             | 1           |
| Battery Pack              | 1           |
| Jumper Wires              | As required |

---

## Pin Connections

### Motor Driver (L298N)

| L298N | XIAO ESP32-C6 |
| ----- | ------------- |
| IN1   | D0            |
| IN2   | D1            |
| IN3   | D2            |
| IN4   | D3            |
| ENA   | D4            |
| ENB   | D5            |

### Ultrasonic Sensor (HC-SR04)

| HC-SR04 | XIAO ESP32-C6 |
| ------- | ------------- |
| VCC     | 5V            |
| GND     | GND           |
| TRIG    | D6            |
| ECHO    | D7            |

---

## Working Principle

1. ESP32-C6 starts a Wi-Fi Access Point.
2. User connects a smartphone to the ESP32 Wi-Fi network.
3. Opening the ESP32 IP address displays the control dashboard.
4. The HC-SR04 continuously measures distance.
5. Distance values are:

   * Displayed on Serial Monitor
   * Updated on the web dashboard
6. User controls robot movement using web buttons.

---

## Wi-Fi Credentials

```text
SSID: RIYA
Password: riya1234
```

Default IP Address:

```text
http://192.168.4.1
```

---

## Web Dashboard

The web dashboard provides:

* Live distance display
* Robot status indicator
* Forward button
* Backward button
* Left button
* Right button
* Stop button

---

## Software Requirements

* Arduino IDE 2.x
* ESP32 Board Package
* WiFi Library
* WebServer Library

---

## Installation

### 1. Install ESP32 Board Package

Open:

Tools → Board Manager

Search:

```text
esp32
```

Install the latest ESP32 package.

### 2. Select Board

```text
Seeed XIAO ESP32-C6
```

### 3. Upload Code

* Connect ESP32-C6 via USB
* Select correct COM port
* Upload the sketch

### 4. Open Serial Monitor

Set baud rate:

```text
115200
```

---

## Usage

### Connect to Wi-Fi

```text
SSID: RIYA
Password: riya1234
```

### Open Browser

Navigate to:

```text
http://192.168.4.1
```

### Control Robot

Use the web buttons to:

* Move Forward
* Move Backward
* Turn Left
* Turn Right
* Stop

Monitor live distance measurements on the same page.

---

## Project Applications

* Wi-Fi Robot Control
* Distance Measurement System
* Educational Robotics
* IoT Learning Projects
* Mobile-Controlled Robots
* Sensor Monitoring Systems

---

## Future Improvements

* Obstacle Avoidance Mode
* Autonomous Navigation
* Speed Control Using PWM
* Battery Monitoring
* Live Sensor Graphs
* Camera Streaming
* Voice Control

---

## Author

Developed using:

* XIAO ESP32-C6
* HC-SR04 Ultrasonic Sensor
* L298N Motor Driver
* Arduino Framework


