## 📌 Overview
This project is a robotics-based autonomous vehicle capable of following a black line on the ground while detecting and responding to obstacles in its path. The system uses sensors for line tracking, a microcontroller for decision-making, and a motor driver for movement control. The object detection feature ensures collision avoidance, making the buggy suitable for robotics competitions and automation applications.

## 🛠 Features
- **Line Following:** Uses IR sensors to track a predefined path.
- **Object Detection:** Stops or reroutes when an obstacle is detected.
- **Autonomous Navigation:** No manual control needed during operation.
- **Smooth Motion Control:** Uses motor driver with optimized PWM signals.

## 🧰 Components Used
- Microcontroller (Arduino r)
- IR Line Sensors
- Ultrasonic Sensor (HC-SR04) for object detection
- Motor Driver (L298N )
- DC Motors with Wheels
- Chassis and Power Supply

## ⚙ How It Works
1. IR sensors continuously scan the surface to detect the black line.
2. The microcontroller processes sensor data to adjust motor speeds.
3. Ultrasonic sensor checks for obstacles ahead.
4. If an object is detected within the threshold distance, the buggy stops until the path is clear.

## 🚀 Future Improvements
- Adding PID control for smoother line tracking.
- Implementing Bluetooth/WiFi control modes.
- Adding camera-based object recognition.
