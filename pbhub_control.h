#pragma once
#include "esphome.h"
#include "esphome/components/i2c/i2c.h"

class PbHubController {
public:
  esphome::i2c::I2CBus *bus = nullptr;
  const uint8_t HUB_ADDR = 0x61;
  const uint8_t US_ADDR = 0x57;

  void init(esphome::i2c::I2CBus *i2c_bus) {
    bus = i2c_bus;
  }

  void set_pump(int channel, bool state) {
    if (!bus) return;
    
    // 0x01 is the Digital Write register for the WHITE wire (IO1)
    uint8_t reg_addr = 0x40 + (channel * 0x10) + 0x01; 
    uint8_t data[2] = {reg_addr, (uint8_t)(state ? 1 : 0)};
    
    bus->write(HUB_ADDR, data, 2);
  }

  int read_moisture(int channel) {
    if (!bus) return 0;
    
    // 0x06 is the Analog Read register for the YELLOW wire (IO0)
    uint8_t reg_addr = 0x40 + (channel * 0x10) + 0x06; 
    uint8_t data[2] = {0, 0};
    
    if (bus->write(HUB_ADDR, &reg_addr, 1) != esphome::i2c::ERROR_OK) return 0;
    
    // Wait 10ms for the hub to switch ports
    delay(10); 
    
    if (bus->read(HUB_ADDR, data, 2) != esphome::i2c::ERROR_OK) return 0;
    
    return data[0] | (data[1] << 8);
  }

  float read_ultrasonic() {
    if (!bus) return NAN;
    uint8_t cmd = 0x01; 
    
    // 3-STRIKE RETRY LOOP to prevent "Disconnected" drops
    for (int attempts = 0; attempts < 3; attempts++) {
      if (bus->write(US_ADDR, &cmd, 1) == esphome::i2c::ERROR_OK) {
        delay(120); 

        uint8_t data[3] = {0, 0, 0};
        if (bus->read(US_ADDR, data, 3) == esphome::i2c::ERROR_OK) {
          uint32_t raw_data = (data[0] << 16) | (data[1] << 8) | data[2];
          float dist_mm = raw_data / 1000.0;
          
          if (dist_mm > 0.0 && dist_mm < 4500.0) {
            return dist_mm / 10.0; 
          }
        }
      }
      delay(50); 
    }
    return NAN; 
  }
};

PbHubController pbhub;