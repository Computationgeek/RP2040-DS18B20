# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.12)

# Set compiler paths explicitly
set(CMAKE_C_COMPILER /home/aamir/.pico-sdk/toolchain/14_2_Rel1/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER /home/aamir/.pico-sdk/toolchain/14_2_Rel1/bin/arm-none-eabi-g++)

include(pico_sdk_import.cmake)

project(ds18b20_test)

set(PICO_STDIO_USB 1)
set(PICO_STDIO_UART 0)

pico_sdk_init()

add_executable(ds18b20_test
    main.cpp
    DS18B20.cpp
)

target_link_libraries(ds18b20_test
    pico_stdlib
    hardware_gpio
)

pico_add_extra_outputs(ds18b20_test)
