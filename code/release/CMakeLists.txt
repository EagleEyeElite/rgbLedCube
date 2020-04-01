cmake_minimum_required(VERSION 3.15)

set(PRODUCT_NAME rgbLedCube)

file(GLOB_RECURSE SRC_FILES "*.c" "*.cpp" "*.h") # Load all files in src folder

# Create one target
add_executable(${PRODUCT_NAME} ${SRC_FILES})

# Rename the output to .elf as we will create multiple files
# set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ../output.elf)

# Rename the output to .elf as we will create multiple files
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME output.elf DEPENDS ${PRODUCT_NAME})
