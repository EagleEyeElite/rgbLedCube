cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

# Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)

# Project name
project(rgbLedCube ASM C CXX)
set(PRODUCT_NAME rgbLedCube)


## AVR Chip Configuration
set(F_CPU 2000000UL)
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
set(MCU atmega1284p)
# Default Baudrate for UART, read avr include/util/setbaud.h for usage
set(BAUD 9600)
set(USB_Port /dev/cu.usbmodem002985422)

# AVR Fuses, configured for hardware
# http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega1284p
set(L_FUSE 0xff)
set(H_FUSE 0xd9)
set(E_FUSE 0xfc)
set(LOCK_BIT 0xff)

# Pass defines to compiler
add_definitions(
        -DF_CPU=${F_CPU}
        -DBAUD=${BAUD}
)
# mmcu MUST be passed to bot the compiler and linker, this handle the linker
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

add_compile_options(
        -mmcu=${MCU} # MCU
        -Os # optimize
        -Wall # enable warnings
        -Wno-main
        -Wundef
        -Wfatal-errors
        -Wl,--relax,--gc-sections
        -g
        -gdwarf-2
        -funsigned-char # a few optimizations
        -funsigned-bitfields
        -fpack-struct
        -fshort-enums
        -ffunction-sections
        -fdata-sections
        -fno-split-wide-types
        -fno-tree-scev-cprop
)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c18")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.c" "src/*.h" "src/*.s")
# Create one target
add_executable(${PRODUCT_NAME} ${SRC_FILES})

# Rename the output to .elf as we will create multiple files
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME output.elf DEPENDS ${PRODUCT_NAME})

add_custom_target(strip ALL avr-strip output.elf DEPENDS ${PRODUCT_NAME})

# Transform binary into hex file, we ignore the eeprom segments in the step
add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex output.elf output.hex DEPENDS strip)
# Transform binary into hex file, this is the eeprom part (empty if you don't
# use eeprom static variables)
add_custom_target(eeprom avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex output.elf output.eep DEPENDS strip)

# arduino as isp: avrdude -c stk500v1 -b 19200 -P /dev/ttyACM0 -p atmega1284p -t
# Pololu USB AVR Programmer v2.1 stk500: avrdude -c stk500 -b 115200 -P /dev/ttyACM0 -p atmega1284p -B 0.5 -t
# The programmer to use, read avrdude manual for list
set(PROG_TYPE -c stk500 -b 115200 -P ${USB_Port} -p ${MCU} -B 0.5)

# Upload the firmware with avrdude
add_custom_target(upload avrdude ${PROG_TYPE} -V -U flash:w:output.hex DEPENDS hex)

# Upload the eeprom with avrdude
add_custom_target(upload_eeprom avrdude ${PROG_TYPE} -V -U eeprom:w:output.eep DEPENDS eeprom)

# Burn fuses
add_custom_target(fuses avrdude ${PROG_TYPE} -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m -U lock:w:${LOCK_BIT}:m)

# Clean extra files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "output.hex;output.eeprom;output.lst")
