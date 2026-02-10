#include <stdio.h>
#include "pico/stdlib.h"
#include "DS18B20.h"

int main() {
    stdio_init_all();
    sleep_ms(2000);
    
    DS18B20 sensor(1);
    
    if (sensor.begin()) {
        while (true) {
            float temp = sensor.readTemperature();
            printf("%.2f\n", temp);
            sleep_ms(1000);
        }
    }
    
    return 1;
}
