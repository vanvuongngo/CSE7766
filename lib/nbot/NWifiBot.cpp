// -----------------------------------------------------------------------------
// NWifiBot 
// Copyright (C) 2021 by Van Vuong Ngo <vanvuongngo at github dot com>
// -----------------------------------------------------------------------------

#include "NWifiBot.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <RemoteDebug.h> //https://github.com/JoaoLopesF/RemoteDebug

bool NWifiBot::_ready = false; 
const char * NWifiBot::_ssid = "sonoff";
const char * NWifiBot::_password = "";

NWifiBot::~NWifiBot()
{
}

void NWifiBot::begin(String hostname)
{
    _setupConnection(hostname);

    _ready = true;
}

void NWifiBot::_setupConnection(String hostname)
{
  // Create a network
  Serial.print("Creating access point named: ");
  Serial.println(_ssid);
  if (!WiFi.softAP(_ssid, _password))
  {
    Serial.println("Failed to create access point");
    // reset
  }
  Serial.print("IP address: ");
  IPAddress apIP = WiFi.softAPIP();
  Serial.println(apIP);


/*
// TODO: setup credentials over a webserver and connect as a client
    // WiFi connection
    WiFi.begin(ssid, password);
    Serial.println("");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.print("IP address: ");
    IPAddress apIP = WiFi.getIP();
    Serial.println(apIP);
*/
  // Register host name in mDNS
  WiFi.hostname(hostname + ".local");
  if (MDNS.begin(hostname))
  {
    Serial.print("* MDNS started. Hostname -> ");
    Serial.println(hostname);
  }
}
