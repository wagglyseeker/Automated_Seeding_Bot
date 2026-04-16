# 🌱 Automated Seeding Robot with Mobile-Based Wireless Control

An embedded IoT-based robotic system designed to automate the process of drilling, seeding, covering, and irrigation.  
The system integrates wireless mobile control, sensor-based automation, and multi-actuator coordination to improve efficiency in agricultural tasks.

---

## 📌 Overview

This project focuses on developing an automated robotic system capable of performing agricultural seeding operations with minimal human intervention.

The robot performs sequential operations including:

1. Navigation across soil
2. Drilling holes using servo-controlled mechanisms
3. Dispensing seeds into drilled positions
4. Covering seeds using a mechanical flap
5. Monitoring soil moisture
6. Activating irrigation when required

The system supports both *manual control via mobile application* and *automated irrigation based on sensor feedback*.

---

## 🧠 Key Features

- Multi-directional robotic movement control
- Wireless mobile-based operation
- Automated drilling and seed dispensing
- Soil moisture-based irrigation system
- Multi-actuator coordination
- Sequential task automation
- Sensor-driven decision logic

---

## 🏗️ System Architecture

The system consists of three major modules:

---

### 1️⃣ Control System

Responsible for:

- Motion control logic
- Actuator coordination
- Sensor input processing
- Task sequencing

Key Functions:

- Movement control
- Drilling control
- Seed dispensing control
- Flap operation
- Irrigation control

---

### 2️⃣ Wireless Mobile Interface

Responsible for:

- Remote robot control
- Command transmission
- Device connectivity
- User interaction

Key Features:

- Wireless connection to robot
- Manual directional control
- Command-based task execution

---

### 3️⃣ Sensor-Based Irrigation System

Responsible for:

- Monitoring soil moisture levels
- Triggering water pump activation
- Preventing overwatering

Key Features:

- Real-time soil monitoring
- Threshold-based irrigation
- Automated watering process

---

## 🧰 Technologies Used

- Embedded Systems Development
- Embedded C/C++
- Arduino Platform
- Wireless Communication Systems
- Motor Control Systems
- Sensor Integration
- Mobile Application Development
- IoT Systems

---

## ⚙️ Working Principle

The robot follows a structured workflow:

1. Robot moves to target location
2. Drilling mechanism creates hole
3. Seed dispensing mechanism releases seed
4. Flap mechanism covers seed
5. Soil moisture sensor checks soil condition
6. Water pump activates if moisture level is low

This sequence enables efficient and automated planting.

---
