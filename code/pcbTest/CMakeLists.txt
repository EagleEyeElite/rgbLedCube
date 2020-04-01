cmake_minimum_required(VERSION 3.15)

set(PRODUCT_NAME pcbTest)

file(GLOB_RECURSE SRC_FILES2 "*.c" "*.cpp" "*.h") # Load all files in src folder

# Create one target
add_executable(${PRODUCT_NAME} ${SRC_FILES2})

# Rename the output to .elf as we will create multiple files
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ../output.elf)

# add_custom_target(test PRE-BUILD COMMAND rm ../output.elf DEPENDS ${PRODUCT_NAME})