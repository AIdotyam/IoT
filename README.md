# **AI.yam IoT System**

## **Description**

  The IoT component serves as an auxiliary tool that triggers a buzzer and sends notifications via a Telegram bot using a webhook. Once the Mobile Development application detects a dead chicken, the backend system triggers the Telegram bot by sending an ON_buzzer message through the webhook. The bot then activates the IoT buzzer, displays a "dead chicken" message on the I2C LCD, and sends an alert notification via Telegram.

---

## **Features**

- Automatic detection and alert for dead chickens.
- Trigger an IoT buzzer and display alerts on an I2C LCD.
- Notify users via Telegram bot.

---

## **Prerequisites**

To use this IoT system, ensure you have:
1. Hardware:
  - ESP32-WROOM-32
  - LED
  - Resistor 100Ohm
  - Mini UPS 5V/2A
  - I2C LCD (16x2)
  - Buzzer Speaker

2. Software and Tools:
  - Arduino IDE
  - Telegram
  - IFTTT Webhook

3. Libraries:
```bash
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
```

---

## **Installation**

1. Setup the Hardware:
  - Connect the ESP32 to the I2C LCD, LED, and buzzer as per the circuit diagram.
  - Ensure the Mini UPS powers the ESP32 and other components.

2. Configure the Arduino IDE:
  - Install the necessary libraries listed above.
  - Configure the ESP32 board in Arduino IDE settings.

3. Telegram Bot and Webhook:
  - Create a Telegram bot using BotFather.
  - Link the bot with IFTTT for webhook integration.

4. Deploy the Code:
  - Upload the provided C++ code to the ESP32.


---

## **System Design**

**Architecture**
![Architecture](https://github.com/AIdotyam/IoT/blob/main/Architecture/IoT[1].png)

The IoT system is integrated with the AI.yam project architecture, using Firebase and Cloud functions to handle backend logic and trigger the IoT actions. The IoT system interacts with the mobile application, cloud, and Telegram bot.

**Workflow**
![WORKFLOW](https://github.com/AIdotyam/IoT/blob/main/Architecture/IoT.png)
1. The backend sends a webhook message (ON_buzzer) to the Telegram bot.
2. The Telegram bot activates the IoT buzzer and sends a notification to users.
3. The I2C LCD displays a "dead chicken" message for immediate physical alert.

**How It Works**
1. ESP32 connects to Wi-Fi and listens for incoming messages from the Telegram bot.
2. When the ON_buzzer command is received, the buzzer is activated, and the LCD displays the alert.
3. Users receive a notification via Telegram to take appropriate actions.



---

## **License**

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
