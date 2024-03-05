# esphome/external_components/d3_sensor/__init__.py

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_DATA
from .. import uart_ns, validate_raw_data

CODEOWNERS = ["@ssieb"]

DEPENDENCIES = ["uart"]

D3Sensor = uart_ns.class_("D3Sensor", cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(D3Sensor),
            cv.Required(CONF_DATA): validate_raw_data,
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    data = config[CONF_DATA]
    if isinstance(data, bytes):
        data = [cg.RawExpression(x) for x in data]
    cg.add(var.set_data(data))
