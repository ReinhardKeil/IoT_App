#!/bin/bash
sed -i "s/WIFI_ESP8266_SERIAL_DRIVER *[0-9]/WIFI_ESP8266_SERIAL_DRIVER          $ARDUINO_USART_NUMBER/" "RTE/CMSIS_Driver/WiFi_ESP8266_Config.h"
