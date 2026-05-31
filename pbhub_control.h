#pragma once
#include "esphome.h"
#include "esphome/components/i2c/i2c.h"

class PbHubController {
public:
  esphome::i2c::I2CBus *bus = nullptr;
  const uint8_t HUB_ADDR = 0x61;
  const uint8_t US_ADDR = 0x57;

  // We initialize this directly from the YAML config
  void init(esphome::i2c::I2CBus *i2c_bus) {
    bus = i2c_bus;
  }

  void set_pump(int channel, bool state) {
    if (!bus) return; // Safety check
    // Calculate the correct register for the channel (CH0=0x40, CH1=0x50, etc.)
    uint8_t reg_base = 0x40 + (channel * 0x10); 
    
    // Write 3 bytes: [Register, State, Padding Byte]
    uint8_t data[3] = {reg_base, (uint8_t)(state ? 1 : 0), 0};
    bus->write(HUB_ADDR, data, 3);
  }

  int read_moisture(int channel) {
    if (!bus) return 0;
    uint8_t reg_base = 0x40 + (channel * 0x10);
    uint8_t reg_addr = reg_base + 0x06; // 0x06 is the 10-bit Analog Read command
    uint8_t data[2] = {0, 0};
    
    // Write the register address we want to read from
    if (bus->write(HUB_ADDR, &reg_addr, 1) != esphome::i2c::ERROR_OK) return 0;
    
    // Read the 2 bytes back (Low byte, then High byte)
    if (bus->read(HUB_ADDR, data, 2) != esphome::i2c::ERROR_OK) return 0;
    
    return data[0] | (data[1] << 8);
  }

  float read_ultrasonic() {
    if (!bus) return NAN;
    uint8_t cmd = 0x01; // 0x01 tells the sensor to ping
    
    if (bus->write(US_ADDR, &cmd, 1) != esphome::i2c::ERROR_OK) return NAN;

    // Give the soundwave time to bounce back
    delay(120); 

    // Request the 3 bytes of distance data
    uint8_t data[3] = {0, 0, 0};
    if (bus->read(US_ADDR, data, 3) == esphome::i2c::ERROR_OK) {
      uint32_t raw_data = (data[0] << 16) | (data[1] << 8) | data[2];
      float dist_mm = raw_data / 1000.0;
      return dist_mm / 10.0; // Return converted to centimeters
    }
    return NAN;
  }
};

// Create a global instance so ESPHome can use it
PbHubController pbhub;
