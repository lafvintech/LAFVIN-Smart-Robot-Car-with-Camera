
#ifndef _AP_CAM_SERVER_H
#define _AP_CAM_SERVER_H
#include "esp_camera.h"
#include <WiFi.h>

class CameraNetworkHandler
{

public:
  void begin(void);
  String accessPointSSID;

private:
  const char *ssid = "LAFVIN-";
  const char *password = "";
};

#endif
