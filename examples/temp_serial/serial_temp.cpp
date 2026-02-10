#include <stdio.h> //This header is added to use the standard Input/Output functions like printf
#include "pico/stdlib.h" // This header is added to use the standard function of the RP2040, like GPIO, sleep, and initialization of stdio
#include "DS18B20.h" //This header is added to include the DS18B20 class definition and its member functions

int main() { //Main function where the execution of the program starts
    // Initialize LED
    const uint LED_PIN = PICO_DEFAULT_LED_PIN; //Declare a constant variable LED_PIN to store the default LED_PIN nummber of RP2040
    gpio_init(LED_PIN);  // This initializes the GPIO pin for LED
    gpio_set_dir(LED_PIN, GPIO_OUT); //This line sets the direction of the GPIO pin as OUTPUT to control the LED
    
    
    for(int i = 0; i < 3; i++) { // For loop to iterate 3 times to blink the inbuilt LED to show that the program has started
        gpio_put(LED_PIN, 1); // This line turns ON the LED by setting the GPIO pin HIGH
        sleep_ms(100); //this delay is added to keep the LED for 100ms in ON state
        gpio_put(LED_PIN, 0); // This line turns OFF the LED by setting the GPIO pin low for 100ms
        sleep_ms(100);
    }
    
    stdio_init_all(); // This line intialize stdio for RP2040 to use serial communication functions like printf
    

    sleep_ms(1000);// This delay is to ensure that serial communication is properly initialized before using it
    
    
    DS18B20 sensor(1); // The sensor object is created of the DS18B20 class, where gpio pin 1 is used to connect the data pin of the DS18B20 sensor
    
    if (!sensor.begin()) { // This condition checks if the sensor is connected or not using the begin function of the DS18B20 class
        printf("ERROR: Sensor not found!\n"); // This line prints the error message to show whether the sensor is not found
        // Blink LED fast to indicate error
        while(true) { // Infinite loop to blink LED         until the sensor is connected
            gpio_put(LED_PIN, 1); 
            sleep_ms(100);
            gpio_put(LED_PIN, 0);
            sleep_ms(100);
        }
    }
    
    printf("SUCCESS: Sensor found!\n"); 
    
    while (true) {
        float temp = sensor.readTemperature(); // This line reads the temperature from the sensor using the readTemperature function of the DS18B20 class
        printf("Temperature: %.2f C\n", temp); // This line prints the read temperature value on the serial monitor 
        // Sensor is connected, LED blinks with a 50ms delay to show that the sensor is working fine and sending data to the RP2040
        // Blink LED once per reading
        gpio_put(LED_PIN, 1);
        sleep_ms(50); 
        gpio_put(LED_PIN, 0);
        
        sleep_ms(500);
    }
    
    return 0; 
}
