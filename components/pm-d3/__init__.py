# config/d3_sensor/__init__.py

DEPENDENCIES = ["uart"]

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    cg.add(var.set_data(config[CONF_DATA]))
