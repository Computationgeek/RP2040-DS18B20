/**
 * DS18B20 Pico Library
 * Copyright (c) 2024 Team Disruptors. All rights reserved.
 * Proprietary software - unauthorized use prohibited.
 */
#include <cstdint>  //This line was added to for uint8_t definition
#include "DS18B20.h" //This line was added to include the header file for the D18B20 Class
#include "hardware/gpio.h" //header is added to use the GPIO fucntions of the RP2040


DS18B20::DS18B20(uint pin) : gpio_pin(pin) {} //This line was added to initialize the gpio_pin member variable with the provided pin number

bool DS18B20::begin() { // This line helps to intialise the GPIO pin & check if the sensor is connected
    gpio_init(gpio_pin); // Line initializes the specified GPIO pin for use
    gpio_pull_up(gpio_pin); // This line enables the pull_up for the preffered GPIO pin for sensor
    return onewire_reset(); /* This line checks if the sensor is cconnected for performing one wire reset which is necessary for 
    sensor to start communication where if the sensor is connected it returns 0 else 1 */
}

bool DS18B20::isConnected() { // This line checks if snesor is conencted by performing one wire reset
    return onewire_reset(); // This line returns teh value of one wire reset function which is 0 if connected or 1 if not connected
}

bool DS18B20::onewire_reset() { // This lines helps to perform one wire reset
    gpio_set_dir(gpio_pin, GPIO_OUT); // Sets the GPIO pin as output
    gpio_put(gpio_pin, 0);// Sets the GPIO pin high for one wire reset
    sleep_us(480); //This delay for 480 millseconds is to ensure that sensor detects the reset signal
    
    gpio_set_dir(gpio_pin, GPIO_IN); //sets the gpio_pin as input for detecting return presence pulse from the sensor 
    sleep_us(70); // Which makes the GPIO pin to wait for 70ms to read the pulse
    
    bool presence = !gpio_get(gpio_pin); // If the presense pulse is detected from returns as 1 it means sensor is connected else 0 if not connected
    sleep_us(410); //This process waits for 410ms to complete the reset_sequence
    
    return presence; // Retuns the prsense value to the calling function 
}

void DS18B20::onewire_write(uint8_t data) { // This line helps to write a byte(8-bits) of data to sensor for starting communication & scratchpad read/write

    /*Scratch pad RAM in DS18B20 sensor is used to store temprature data & config setiings which is 9 bytes long (8x9 = 72 bits) 
    also this scratchpad ram is temporary storage area for data being transferred to/from sensor */

    /* Scratchpad is 9-byte temporary storage in DS18B20 containing:
   - Bytes 0-1: Temperature reading
   - Byte 2: High alarm
   - Byte 3: Low alarm  
   - Byte 4: Configuration
   - Bytes 5-7: Reserved
   - Byte 8: CRC */
    
    for (int i = 0; i < 8; i++) { //For loop to iterate through each bit of the byte to be written to scratchpad RAM and i < 8 is based on 8-bits in a byte
        gpio_set_dir(gpio_pin, GPIO_OUT); // sets the GPIO pin as O/P to start the write process(temperature conversion) to scratchpad
        gpio_put(gpio_pin, 0); //If GPIo returns 0 it means writing process has started
        sleep_us(1); // This delay is to esnure that the write process has initiated
        
        if (data & 1) {/* This condition checks if the Least significant bit(LSB) of the data byte is 1 or 0 
            (LSB endian is used here so first bit written is LSB either 0 or 1) */
            gpio_set_dir(gpio_pin, GPIO_IN); //Sets the gpio pin as input to write 1 to scratchpad so that sensor can start temperature conversion
        }
        
        sleep_us(60); // Delay is added to ensure that previous write oeration is completed or not
        gpio_set_dir(gpio_pin, GPIO_IN); // Sets the GPIO_pin as I/P to end the write process
        sleep_us(1); // This short delay was to ensure that write proces has ended
        data >>= 1; // >>= is the a bitwise right shift operator which shifts write data by 1 bit to write the next bit in the next iteration where LSB is written
    }
}

uint8_t DS18B20::onewire_read() { //This line helps to read the byte of data from the sensor to get the temperature value where it is send to RP2040
    uint8_t data = 0; // This line initializes data variable to store the read byte from the sensor
    
    for (int i = 0; i < 8; i++) { // For loop to iterate between 8-bits to read the complete byte from the sensor

        gpio_set_dir(gpio_pin, GPIO_OUT); // Sets the GPIO pin as O/P to start the read process from the sensor
        gpio_put(gpio_pin, 0); //If the return value is 0 it means read process has started
        sleep_us(1); // This small delay is to ensure that read process has started
        
        gpio_set_dir(gpio_pin, GPIO_IN); //Sets the GPIO pin as I/P to read the bit fromm the sensor
        sleep_us(14);// This delay is to ensure that pico waits for 14us before reading the bit from sensor
        
        if (gpio_get(gpio_pin)) { // This condition checks if th read bit from the sensor is 1 or 0 that is used to determine the temperature value
            data |= (1 << i); // if the read b it is 1 it sets the corresponding bit in the data variable using biteware OR & left shift operation
        }
        
        sleep_us(45); // This delay is ensures that the read operation has completed all 8 byte iteration
    }
    
    return data; // Returns the read byte to the calling function
}

float DS18B20::readTemperature() { // This line helps to read the temperature value from the sensor in Celsius format
    // Start conversion
    onewire_reset();
    onewire_write(0xCC); // Skip ROM
    onewire_write(0x44); // Convert temperature
    
    // Wait for conversion
    sleep_ms(750);
    
    // Read scratchpad
    onewire_reset();
    onewire_write(0xCC); // Skip ROM
    onewire_write(0xBE); // Read scratchpad
    
    // Read temperature data
    uint8_t data[2];
    data[0] = onewire_read(); // LSB
    data[1] = onewire_read(); // MSB
    
    // Convert to temperature
    int16_t temp = (data[1] << 8) | data[0];
    return temp / 16.0f;
}

float DS18B20::readCelsius() {
    return readTemperature();
}

float DS18B20::readFahrenheit() {
    return (readTemperature() * 9.0f / 5.0f) + 32.0f;
}
