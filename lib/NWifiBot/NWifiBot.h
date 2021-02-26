// -----------------------------------------------------------------------------
// NWifiBot 
// Copyright (C) 2021 by Van Vuong Ngo <vanvuongngo at github dot com>
// -----------------------------------------------------------------------------

#ifndef NWifiBot_h
#define NWifiBot_h

#include "Arduino.h"

class NWifiBot
{

public:
  NWifiBot() {};
  virtual ~NWifiBot();

  static void begin(const String & hostname);

private:
  static bool _ready;

  // default SSID and password
  static const char * _ssid;
  static const char * _password;

  static void _setupConnection(const String & hostname);

};

#endif
