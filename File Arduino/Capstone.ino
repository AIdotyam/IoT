#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Wi-Fi Credentials
const char* ssid = "BuzzerOK";
const char* password = "1234567890";

// Bot Telegram Token
const char* botToken = "7286469685:AAEzJrjszx1xjDNLI8g3U2ar-x93jtTIbi4";

// ID Grup Telegram
const String chatGroupId = "-1002368666400";

// Objek Wi-Fi dan bot
WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

unsigned long lastTimeBotRan;
const int botRequestDelay = 1000;

// LCD I2C (alamat 0x27, ukuran 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin untuk LED dan Buzzer
const int ledPin = 15;
const int buzzerPin = 4;

// Status buzzer
bool buzzerActive = false;

// Variabel untuk LED berkedip
unsigned long previousMillisLED = 0;
const int ledBlinkInterval = 500; 
bool ledState = false;

// Fungsi untuk menghubungkan ke Wi-Fi
void connectWiFi() {
  Serial.print("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi terhubung.");
}

// Fungsi untuk memproses pesan baru
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    // Log pesan untuk debugging
    Serial.println("Pesan baru diterima: " + text);

    // Filter hanya pesan dari grup tertentu
    if (chat_id == chatGroupId) {
      Serial.println("Pesan dari grup terdeteksi.");

      if (text.indexOf("/ON_buzzer") != -1) {
        Serial.println("Perintah /ON_buzzer diterima!");
        bot.sendMessage(chat_id, "Buzzer diaktifkan!", "");

        // Aktifkan buzzer dan LED, ubah pesan LCD
        buzzerActive = true;
        lcd.clear();
        lcd.setCursor((16 - 9) / 2, 0); 
        lcd.print("Peringatan");
        lcd.setCursor((16 - 10) / 2, 1);
        lcd.print("Ayam Mati!");
      }

      if (text.indexOf("/OFF_buzzer") != -1) {
        Serial.println("Perintah /OFF_buzzer diterima!");
        bot.sendMessage(chat_id, "Buzzer dimatikan!", "");

        // Nonaktifkan buzzer dan LED, kembalikan pesan LCD ke awal
        buzzerActive = false;
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
        lcd.clear();
        lcd.setCursor((16 - 7) / 2, 0); 
        lcd.print("WELCOME");
        lcd.setCursor((16 - 6) / 2, 1); 
        lcd.print("AI.yam");
      }
    }
  }
}

void setup() {
  // Inisialisasi Serial dan pin
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor((16 - 7) / 2, 0);
  lcd.print("AI.yam");
  lcd.setCursor((16 - 6) / 2, 1);
  lcd.print("Prototype");

  // Hubungkan ke Wi-Fi
  connectWiFi();

  // Atur koneksi client
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}

void loop() {
  // Cek apakah Wi-Fi masih terhubung
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  // Periksa pesan baru dari Telegram
  if (millis() > lastTimeBotRan + botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

  // Jika buzzer aktif, hidupkan LED berkedip dan nyalakan buzzer secara terus-menerus
  if (buzzerActive) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisLED >= ledBlinkInterval) {
      previousMillisLED = currentMillis;
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
    // Menyalakan buzzer terus-menerus tanpa nada
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW); 
  }
}
