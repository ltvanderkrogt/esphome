// config/d3_sensor/d3_sensor.cpp

#include "esphome/core/log.h"
#include "d3_sensor.h"

namespace esphome {
namespace d3_sensor {

static const char *const TAG = "d3_sensor";

void D3Sensor::process_data() {
    if (this->available() >= 32) {
        if (this->read_byte() == 0x42 && this->read_byte() == 0x4D) {
            std::array<uint8_t, 32> data;
            for (uint8_t &byte : data) {
                byte = this->read_byte();
            }
            uint16_t received_checksum = (data[30] << 8) | data[31];
            uint16_t calculated_checksum = this->calculate_checksum(data);

            if (received_checksum == 0xFFFF || received_checksum == calculated_checksum) {
                this->publish_state(data);
            }
        }
    }
}

uint16_t D3Sensor::calculate_checksum(const std::array<uint8_t, 32> &data) {
    uint16_t checksum = 0;
    for (uint8_t i = 0; i < 30; i++) {
        checksum += data[i];
    }
    return checksum;
}

void D3Sensor::dump_config() { LOG_SENSOR("", "D3 Sensor", this); }

}  // namespace d3_sensor
}  // namespace esphome
