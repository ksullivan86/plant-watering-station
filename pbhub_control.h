#include "esphome.h"
#include <M5_PbHub.h>

// Global instance of the M5Stack hub
M5_PbHub myPbHub;
bool pbhub_initialized = false;

// ---------------------------------------------------------
// Custom Switch for the Water Pumps
// ---------------------------------------------------------
class PbHubSwitch : public Component, public Switch {
 public:
  uint8_t channel;
  
  PbHubSwitch(uint8_t ch) : channel(ch) {}

  void setup() override {
    if (!pbhub_initialized) {
      Wire.begin(2, 1); // NanoC6 Grove SDA=2, SCL=1
      myPbHub.begin();
      pbhub_initialized = true;
    }
  }

  void write_state(bool state) override {
    myPbHub.digitalWrite(channel, state ? 1 : 0);
    publish_state(state);
  }
};

// ---------------------------------------------------------
// Custom Sensor for the Moisture Probes
// ---------------------------------------------------------
class PbHubSensor : public PollingComponent, public Sensor {
 public:
  uint8_t channel;

  PbHubSensor(uint8_t ch) : PollingComponent(5000), channel(ch) {}

  void update() override {
    int raw_moisture = myPbHub.analogRead(channel);
    publish_state(raw_moisture);
  }
};

// ---------------------------------------------------------
// Custom Sensor for M5Stack I2C Ultrasonic (Address 0x57)
// ---------------------------------------------------------
class UltrasonicI2C : public PollingComponent, public Sensor {
 public:
  // Poll every 5 seconds
  UltrasonicI2C() : PollingComponent(5000) {}

  void setup() override {
    if (!pbhub_initialized) {
      Wire.begin(2, 1);
      pbhub_initialized = true;
    }
  }

  void update() override {
    // Tell the sensor to take a reading
    Wire.beginTransmission(0x57);
    Wire.write(0x01);
    if (Wire.endTransmission() != 0) {
        publish_state(NAN); // Sensor disconnected/error
        return;
    }

    // Use ESPHome's non-blocking timeout to wait for the echo (120ms)
    // This prevents the ESP32 from crashing while waiting for the soundwave
    set_timeout(120, [this]() {
      Wire.requestFrom(0x57, 3);
      if (Wire.available() >= 3) {
        uint32_t raw_data = (Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
        float dist_mm = raw_data / 1000.0;
        publish_state(dist_mm / 10.0); // Convert to cm for Home Assistant
      }
    });
  }
};
