# CSE7766 Firmware

CSE7766 ESP8266 Arduino library and firmware
https://github.com/vanvuongngo/CSE7766.git
fork of https://github.com/ingeniuske/CSE7766.git

## CSE7766_basic

Created stand alone library for the Sonoff Pow R2 power switch with energy monitor witch uses the CSE7759/ CSE7766 as power monitor sensor.
Based upon the excelent espurna platform of Xose Pérez "Home automation firmware for ESP8266-based devices"

https://github.com/xoseperez/espurna/blob/dev/code/espurna/sensors/CSE7766Sensor.h

## ATTENTION!

The serial port ground from the Sonoff device is directly connected to AC-mains.
Be carfull it could potentially destroy your devices if connected directly!

For this reason using a telnet as remote debug connection from Joao Lopes and OTA updates.
https://github.com/JoaoLopesF/RemoteDebugApp or
https://github.com/JoaoLopesF/RemoteDebug

## Using Arduino IDE

- copy the directory `lib/CSE7766` into your arduino library directory
- open `example/CSE7766_basic.ino`

## Using Visual Studio Code with platformIO

- modify `src/main.cpp`
- comment out upload_protocol and upload_port if you want to upload over serial port 
- for production if you want to disable debug tool or OTA see platformio.ini
- execute build and flash

## Using precompiled firmware

- install esptool.py see https://github.com/espressif/esptool
- call `esptool.py flash_id` to receive the serial port
- flash e.g. `esptool.py --port /dev/ttyUSB0 write_flash 0x0 cse7766.bin`

## Copyright (C) 2016-2018 by Xose Pérez <xose dot perez at gmail dot com>
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
