cmake_minimum_required(VERSION 3.12)  # Changed from 3.13 to 3.12
include(pico_sdk_import.cmake)

project(DS18B20_Pico)

pico_sdk_init()

# Create library
add_library(DS18B20 
    src/DS18B20.cpp
)

target_include_directories(DS18B20 PUBLIC include)
target_link_libraries(DS18B20 pico_stdlib hardware_gpio)

# Example
add_executable(basic_temp examples/basic_temp/main.cpp)
target_link_libraries(basic_temp DS18B20 pico_stdlib)

pico_add_extra_outputs(basic_temp)
