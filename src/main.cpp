/*
CSE7766_basic with WiFi Access Point

Created stand alone library for the Sonoff Pow R2 power switch with energy monitor witch uses the CSE7759/ CSE7766 as power monitor sensor.
Based upon the excelent espurna platform of Xose Pérez "Home automation firmware for ESP8266-based devices"

https://github.com/xoseperez/espurna/blob/dev/code/espurna/sensors/CSE7766Sensor.h

ATTENTION!

The serial port ground from the Sonoff device is directly connected to AC-mains.
Be carfull it could potentially destroy your devices if connected directly!

For this reason using a telnet as remote debug connection from Joao Lopes and OTA updates.
https://github.com/JoaoLopesF/RemoteDebugApp or
https://github.com/JoaoLopesF/RemoteDebug


Copyright (C) 2016-2018 by Xose Pérez <xose dot perez at gmail dot com>
Copyright (C) 2018 by Ingeniuske  <ingeniuske at gmail dot com>
Copyright (C) 2021 by Van Vuong Ngo https://github.com/vanvuongngo


This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifdef BASIC

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include "RemoteDebug.h" //https://github.com/JoaoLopesF/RemoteDebug
#ifndef OTA_DISABLED
#include <ArduinoOTA.h> // https://docs.platformio.org/en/latest/platforms/espressif8266.html?highlight=ota#over-the-air-ota-update
#endif
#include "CSE7766.h"
#include "NWifiBot.h"

// GPIOs
#define RELAY_PIN 12
#define LED 13

// Check values every 2 seconds
#define UPDATE_TIME 2000

// Debug sensors
#ifndef SENSOR_DEBUG
#define SENSOR_DEBUG 1
#endif

// SSID and password
const char *ssid = "sonoff";
const char *password = "";

// Host mDNS
#define HOST_NAME "sonoff"

CSE7766 myCSE7766;

#ifndef DEBUG_DISABLED
RemoteDebug Debug;
#endif

void setup()
{

  // Debug
  Serial.println("**** Setup: initializing ...");

  // Initialize
  myCSE7766.setRX(1);
  myCSE7766.begin(); // will initialize serial to 4800 bps

  NWifiBot::begin(HOST_NAME);

#ifndef DEBUG_DISABLED
  // Initialize the telnet server of RemoteDebug
  Serial.println("* Arduino RemoteDebug Library");
  MDNS.addService("telnet", "tcp", 23);
  Debug.begin(HOST_NAME);         // Initiaze the telnet server
  Debug.setResetCmdEnabled(true); // Enable the reset command
#endif

#ifndef OTA_DISABLED
  ArduinoOTA.onStart([]() {
    Serial.println("ArduinoOTA start");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nArduinoOTA end");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("End Failed");
    }
  });

  ArduinoOTA.begin();
#endif

  // Close the relay to switch on the load
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  // initialise digital pin LED_SONOFF as an output.
  pinMode(LED, OUTPUT);
}

void loop()
{
  static int mLedState = 0;
  static unsigned long mLastTime = 0;

#ifndef OTA_DISABLED
  // Remote update
  ArduinoOTA.handle();
#endif

#ifndef DEBUG_DISABLED
  // Remote debug over telnet
  Debug.handle();
#endif

  if ((millis() - mLastTime) >= UPDATE_TIME) {

    // Time
    mLastTime = millis();

    // toggle led
    mLedState ^= 1;
    digitalWrite(LED, mLedState);

    debugV("Count of Wifi connected device: %d\n", WiFi.softAPgetStationNum());

    // read CSE7766
    myCSE7766.handle();

    debugD("Voltage %.2f V, Current %.2f A, ActivePower %.2f W, ApparentPower %.2f VA, ReactivePower %.2f VAR, PowerFactor %.0f %%, Energy %.2f Ws",
           myCSE7766.getVoltage(),
           myCSE7766.getCurrent(),
           myCSE7766.getActivePower(),
           myCSE7766.getApparentPower(),
           myCSE7766.getReactivePower(),
           myCSE7766.getPowerFactor(),
           myCSE7766.getEnergy());
  }
}

#endif