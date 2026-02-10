/**
 * DS18B20 Pico Library
 * Copyright (c) 2024 Team Disruptors. All rights reserved.
 * Proprietary software - unauthorized use prohibited.
 */

#pragma once
#include <cstdint>  
#include "pico/stdlib.h"

class DS18B20 {
private:
    uint gpio_pin;
    
    bool onewire_reset();
    void onewire_write(uint8_t data);
    uint8_t onewire_read();
    
public:
    DS18B20(uint pin);
    
    bool begin(); 
    bool isConnected();
    float readTemperature();
    float readCelsius();
    float readFahrenheit();
};
