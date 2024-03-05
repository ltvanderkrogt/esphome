// esphome/external_components/d3_sensor/d3_sensor.cpp

#include "d3_sensor.h"
#include "esphome/core/log.h"

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
                this->print_values(data);
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

void D3Sensor::print_values(const std::array<uint8_t, 32> &data) {
    int pm1_standard = (data[4] << 8) | data[5];
    int pm25_standard = (data[6] << 8) | data[7];
    int pm10_standard = (data[8] << 8) | data[9];

    ESP_LOGD(TAG, "PM1.0: %d ug/m3, PM2.5: %d ug/m3, PM10: %d ug/m3", pm1_standard, pm25_standard, pm10_standard);
}

}  // namespace d3_sensor
}  // namespace esphome
