

#include "sdkconfig.h"

#if CONFIG_LUA_RTOS_LUA_USE_SENSOR

#include <drivers/sensor.h>
#if CONFIG_LUA_RTOS_USE_BINARY_OUTPUT

driver_error_t *binary_output_setup(sensor_instance_t *unit);

// Sensor specification and registration
static const sensor_t __attribute__((used,unused,section(".sensors"))) binary_output__sensor = {
    .id = "BINARY_OUTPUT",
    .interface = {
        {
            .type = GPIO_INTERFACE,

            .flags = SENSOR_FLAG_AUTO_ACQ | SENSOR_FLAG_ON_OFF | SENSOR_FLAG_ON_H(0) | SENSOR_FLAG_ON_L(1) |
                     SENSOR_FLAG_DEBOUNCING | SENSOR_FLAG_DEBOUNCING_THRESHOLD(10000)
        },
    },
    .data = {
        {.id = "value", .type = SENSOR_DATA_INT},
    },
    .interface_name = {"P1"},
	.properties = {
        {.id = "value",       .type = SENSOR_DATA_INT},
    },
    .setup = binary_output_setup
};

driver_error_t *binary_output_setup(sensor_instance_t *unit) {
    // Get initial state
    uint8_t p = gpio_ll_pin_get(unit->setup[0].gpio.gpio);

    if (p == 0) {
        unit->data[0].integerd.value = 1;
    } else {
        unit->data[0].integerd.value = 0;
    }

    unit->latch[0].value.integerd.value = unit->data[0].integerd.value;

    return NULL;
}

#endif
#endif
