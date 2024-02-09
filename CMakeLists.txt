cmake_minimum_required(VERSION 3.17)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
 
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
 
# Add you project name
project(target C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
 
# Add carnel name
set(MCPU cortex-m3)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
# Uncomment for hardware floating point
#add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
#add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
#add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_compile_definitions(STM32L152xE)

# or use this instead of add_compile_definitions == -D CMAKE_CXX_FLAGS=/DMY_MACRO=1 in terminal
add_compile_definitions(ENABLE_LOGGING) # takes about 2%
# add_compile_definitions(ECU)
# add_compile_definitions(ECU_TEST_TRANSMIT_TIMEOUT)

# add_compile_definitions(DEBUG)
# add_compile_definitions(DEBUG_ECU)
# add_compile_definitions(TEST_CAN)
 
# Uncomment for software floating point
add_compile_options(-mfloat-abi=soft)
add_compile_options(-mcpu=${MCPU} -mthumb)
add_compile_options(-ffunction-sections -fdata-sections)
 # -Wall -fdata-sections -ffunction-sections
 
# Uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")
 
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-O0 -g)
endif ()
 
# Add Include directories
include_directories(
        ${CMAKE_SOURCE_DIR}/Core/Inc
        ${CMAKE_SOURCE_DIR}/Core/Inc/UART
        ${CMAKE_SOURCE_DIR}/Core/Inc/I2C
        ${CMAKE_SOURCE_DIR}/Core/Inc/LCD
        ${CMAKE_SOURCE_DIR}/Drivers/STM32L1xx_HAL_Driver/Inc
        ${CMAKE_SOURCE_DIR}/Drivers/STM32L1xx_HAL_Driver/Inc/Legacy
        ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32L1xx/Include
        ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
        )
 
# Add C defines
add_definitions(-DUSE_HAL_DRIVER -DSTM32F334x8)
 
# Add you source file
file(GLOB_RECURSE SOURCES
        "Core/Src/*.*"
        "Core/Src/UART/*.*"
        "Core/Src/I2C/*.*"
        "Core/Src/LCD/*.*"
        "Drivers/STM32L1xx_HAL_Driver/Src/*.c"
        "Core/Startup/startup_stm32l152retx.s"
        )
 
# Add lincer file
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32L152RETX_FLASH.ld)
 
# this options for C++
add_link_options(-specs=nosys.specs -lstdc++)
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=${MCPU} -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})
 
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
 
set(HEX_FILE ${PROJECT_BINARY_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/build/${PROJECT_NAME}.bin)

add_custom_target(flash 
	COMMAND JLinkExe -device ${DEVICE} -speed 4000 -if SWD -CommanderScript ${CMAKE_CURRENT_BINARY_DIR}/flash.jlink 
	DEPENDS ${TARGET}.elf
	)
 
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
