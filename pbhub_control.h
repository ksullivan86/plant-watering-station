#pragma once
#include "esphome.h"
#include <M5_PbHub.h>

class PbHubController {
public:
  M5_PbHub myPbHub;
  bool initialized = false;

  void setup() {
    if (!initialized) {
      Wire.begin(2, 1); // NanoC6 Grove I2C pins: SDA=2, SCL=1
      myPbHub.begin();
      initialized = true;
    }
  }

  void set_pump(int channel, bool state) {
    setup();
    myPbHub.digitalWrite(channel, state ? 1 : 0);
  }

  int read_moisture(int channel) {
    setup();
    return myPbHub.analogRead(channel);
  }

  float read_ultrasonic() {
    setup();
    Wire.beginTransmission(0x57); // M5Stack Ultrasonic I2C address
    Wire.write(0x01);
    
    // If the sensor is unplugged, return NAN (Not A Number)
    if (Wire.endTransmission() != 0) return NAN;

    // Give the soundwave time to bounce back
    delay(120); 

    Wire.requestFrom(0x57, 3);
    if (Wire.available() >= 3) {
      uint32_t raw_data = (Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
      float dist_mm = raw_data / 1000.0;
      return dist_mm / 10.0; // Return in centimeters
    }
    return NAN;
  }
};

// Create a global instance we can easily call from the YAML
PbHubController pbhub;
