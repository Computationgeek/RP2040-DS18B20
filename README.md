# RP2040-DS18B20
A high-performance 12-Bit DS18B20 temperature sensor library for Raspberry Pi Pico RP2040 microcontroller.

## Features

- **Optimized 1-Wire Protocol**: Fast and reliable communication
- **Dual Unit Support**: Celsius and Fahrenheit temperature readings
- **Error Handling**: Robust detection and reporting
- **Simple API**: Easy to integrate and use
- **Production Ready**: Tested and reliable for embedded applications

## Quick Start

### Basic Usage

```cpp
#include "DS18B20.h"

// Create sensor instance on GPIO pin
DS18B20 sensor(2);

// Initialize sensor
if (sensor.begin()) {
    // Read temperature in Celsius
    float celsius = sensor.readCelsius();
    
    // Read temperature in Fahrenheit  
    float fahrenheit = sensor.readFahrenheit();
}
```

## API Reference

### Constructor
```cpp
DS18B20 sensor(pin);
```
- `pin`: GPIO pin number connected to DS18B20 DATA line

### Methods
- `bool begin()` - Initialize sensor, returns true if sensor is found
- `bool isConnected()` - Check if sensor is still connected
- `float readTemperature()` - Read temperature in Celsius
- `float readCelsius()` - Read temperature in Celsius (alias)
- `float readFahrenheit()` - Read temperature in Fahrenheit


## Hardware Configuration

### Pin Connections
```
DS18B20 → Raspberry Pi Pico
VCC    → 3.3V (Pin 36)
GND    → GND (Pin 38)
DATA   → GPIO 1 (Pin 2)
       ↗ 4.7KΩ resistor to 3.3V (Pull-up required)
```

### Required Components
- DS18B20 Temperature Sensor
- 4.7KΩ Resistor (Pull-up between DATA and 3.3V)
- Breadboard and Jumper Wires

## VSCode Setup

### Prerequisites
- Raspberry Pi Pico C/C++ Extension
- Pico SDK installed via extension
- CMake Tools extension

### Project Configuration
1. Create new Pico project using the Pico extension
2. Copy library files to your project
3. Update CMakeLists.txt as shown above
4. Build using `Ctrl+Shift+P` → "CMake: Build"

### Serial Monitor Setup
- **Port**: `/dev/ttyACM0` (Linux) or `COMx` (Windows)
- **Baud Rate**: 115200
- **Line Ending**: None

## Complete Example

```cpp
#include <stdio.h>
#include "pico/stdlib.h"
#include "DS18B20.h"

int main() {
    stdio_init_all();
    sleep_ms(2000); // Wait for serial
    
    DS18B20 sensor(1); // GPIO 1
    
    if (!sensor.begin()) {
        printf("ERROR: Sensor not found on GPIO 1\n");
        return 1;
    }
    
    printf("SUCCESS: Sensor initialized\n");
    
    while (true) {
        float celsius = sensor.readCelsius();
        float fahrenheit = sensor.readFahrenheit();
        
        printf("Temperature: %.2f°C / %.2f°F\n", celsius, fahrenheit);
        sleep_ms(1000);
    }
    
    return 0;
}
```

## Troubleshooting

### Sensor Not Detected
- Verify 4.7KΩ pull-up resistor between DATA and 3.3V
- Check GPIO pin configuration
- Ensure stable 3.3V power supply (do not use 5V)
- Verify ground connections

### Communication Errors
- Keep wire lengths under 1 meter
- Add 100nF decoupling capacitor near sensor
- Check for loose connections
- Ensure single sensor per bus for initial testing

### Build Issues
- Verify PICO_SDK_PATH is set correctly
- Ensure all library files are in proper locations
- Check CMakeLists.txt syntax and dependencies

## Performance Specifications

- **Accuracy**: ±0.5°C (-10°C to +85°C)
- **Temperature Range**: -55°C to +125°C
- **Supply Voltage**: 3.0V to 5.5V
- **Resolution**: User configurable 9-12 bits

## File Structure

```
DS18B20_Pico/
├── include/
│   └── DS18B20.h
├── src/
│   └── DS18B20.cpp
├── examples/
│   └── basic_temp/
│       └── main.cpp
├── CMakeLists.txt
└── README.md
```
## Support

For issues and questions:
1. Check troubleshooting section above
2. Verify hardware connections
3. Ensure proper library integration
4. Test with basic example code first

---

*This library provides a robust interface for DS18B20 temperature sensors with the Raspberry Pi Pico, featuring optimized performance and comprehensive error handling for reliable embedded applications.*
