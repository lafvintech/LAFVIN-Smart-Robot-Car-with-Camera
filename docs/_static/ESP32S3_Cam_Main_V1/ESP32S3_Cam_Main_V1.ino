//#include <EEPROM.h>
#include "AP_CamServer.h"
#include <WiFi.h>
#include "esp_camera.h"
#include "core_version.h"

#ifndef ESP_ARDUINO_VERSION_VAL
#define ESP_ARDUINO_VERSION_VAL(major, minor, patch) ((major << 16) | (minor << 8) | (patch))
#endif

#ifndef ESP_ARDUINO_VERSION
#define ESP_ARDUINO_VERSION ESP_ARDUINO_VERSION_VAL(2, 0, 0)
#endif

WiFiServer server(100);

#define RXD2 3
#define TXD2 40
CameraNetworkHandler camHandler;
bool isWiFiActive = false;

void processClientRequests(void)
{
  static bool hasClientConnected = true;
#if defined(ESP_ARDUINO_VERSION) && ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
  WiFiClient client = server.accept(); // Attempt to create a client object
#else
  WiFiClient client = server.available(); // Attempt to create a client object
#endif
  if (client)                             // If the current client is available
  {
    isWiFiActive = true;
    hasClientConnected = true;
    Serial.println("[Client connected]");
    String readBuff;
    String sendBuff;
    uint8_t Heartbeat_count = 0;
    bool Heartbeat_status = false;
    bool data_begin = true;
    while (client.connected()) // If the client is connected
    {
      if (client.available()) // If there is readable data
      {
        char c = client.read();             // Read a byte
        Serial.print(c);                    // Print from serial port
        if (true == data_begin && c == '{') // Received start character
        {
          data_begin = false;
        }
        if (false == data_begin && c != ' ') // Remove spaces
        {
          readBuff += c;
        }
        if (false == data_begin && c == '}') // Received end character
        {
          data_begin = true;
          if (true == readBuff.equals("{Heartbeat}"))
          {
            Heartbeat_status = true;
          }
          else
          {
            Serial2.print(readBuff);
          }
          //Serial2.print(readBuff);
          readBuff = "";
        }
      }
      if (Serial2.available())
      {
        char c = Serial2.read();
        sendBuff += c;
        if (c == '}') // Received end character
        {
          client.print(sendBuff);
          Serial.print(sendBuff); // Print from serial port
          sendBuff = "";
        }
      }

      static unsigned long Heartbeat_time = 0;
      if (millis() - Heartbeat_time > 1000) // Heartbeat frequency
      {
        client.print("{Heartbeat}");
        if (true == Heartbeat_status)
        {
          Heartbeat_status = false;
          Heartbeat_count = 0;
        }
        else if (false == Heartbeat_status)
        {
          Heartbeat_count += 1;
        }
        if (Heartbeat_count > 3)
        {
          Heartbeat_count = 0;
          Heartbeat_status = false;
          break;
        }
        Heartbeat_time = millis();
      }
      static unsigned long Test_time = 0;
      if (millis() - Test_time > 1000) // Regularly check connected devices
      {
        Test_time = millis();
        //Serial2.println(WiFi.softAPgetStationNum());
        if (0 == (WiFi.softAPgetStationNum())) // If the number of connected devices is "0", send a stop command to the car model
        {
          Serial2.print("{\"N\":100}");
          break;
        }
      }
    }
    Serial2.print("{\"N\":100}");
    client.stop(); // End current connection
    Serial.println("[Client disconnected]");
  }
  else
  {
    if (hasClientConnected == true)
    {
      hasClientConnected = false;
      Serial2.print("{\"N\":100}");
    }
  }
}
/* Used for test stand */
void monitorHardwareEvents(void)
{
  static String readBuff;
  String sendBuff;
  if (Serial2.available())
  {
    char c = Serial2.read();
    readBuff += c;
    if (c == '}') // Received end character
    {
      if (true == readBuff.equals("{BT_detection}"))
      {
        Serial2.print("{BT_OK}");
        Serial.println("Factory...");
      }
      else if (true == readBuff.equals("{WA_detection}"))
      {
        Serial2.print("{");
        Serial2.print(camHandler.accessPointSSID);
        Serial2.print("}");
        Serial.println("Factory...");
      }
      readBuff = "";
    }
  }
  {
    if ((WiFi.softAPgetStationNum())) // If the number of connected devices is not "0", the LED indicator stays on
    {
      if (true == isWiFiActive)
      {
        digitalWrite(46, LOW);
        Serial2.print("{WA_OK}");
        isWiFiActive = false;
      }
    }
    else
    {
      // Get timestamp
      static unsigned long Test_time;
      static bool en = true;
      if (millis() - Test_time > 100)
      {
        if (false == isWiFiActive)
        {
          Serial2.print("{WA_NO}");
          isWiFiActive = true;
        }
        if (en == true)
        {
          en = false;
          digitalWrite(46, HIGH);
        }
        else
        {
          en = true;
          digitalWrite(46, LOW);
        }
        Test_time = millis();
      }
    }
  }
}
void setup()
{
  Serial.begin(115200);
  Serial.print("AP SSID:");
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  //http://192.168.4.1/control?var=framesize&val=3
  //http://192.168.4.1/Test?var=
  camHandler.begin();
  server.begin();
  delay(100);
  pinMode(46, OUTPUT);
  digitalWrite(46, HIGH);
  Serial.println("Good-Luck-to-You-V1.0.1...");
  Serial2.print("{Factory}");
  //ESP.restart();
  // esp_restart();
}
void loop()
{
  processClientRequests();
  monitorHardwareEvents();
}
