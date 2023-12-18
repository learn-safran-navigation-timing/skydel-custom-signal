cmake_minimum_required(VERSION 3.21)

project(CUSTOM_SIGNAL_EXAMPLES
        DESCRIPTION "Skydel Custom Signal Examples"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/custom_signal)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/custom_signal)

add_library(custom_signal INTERFACE)

target_include_directories(custom_signal INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(example_beidou_b1c)
add_subdirectory(example_galileo_e1)
add_subdirectory(example_gps_ca)
add_subdirectory(example_gps_tddm_ca)
add_subdirectory(example_qzss_ca)
