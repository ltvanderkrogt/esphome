// esphome/external_components/d3_sensor/d3_sensor.h

#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include <array>

namespace esphome {
namespace d3_sensor {

class D3Sensor : public uart::UARTDevice, public Component {
 public:
    void process_data();
    void set_data(const std::array<uint8_t, 32> &data) { this->data_ = data; }

 protected:
    uint16_t calculate_checksum(const std::array<uint8_t, 32> &data);
    void print_values(const std::array<uint8_t, 32> &data);

    std::array<uint8_t, 32> data_;
};

}  // namespace d3_sensor
}  // namespace esphome
