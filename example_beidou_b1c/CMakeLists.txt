file(GLOB CUSTOM_B1C_SRC *.cpp)
file(GLOB CUSTOM_COMMON "../common/*.cpp")
list(APPEND CUSTOM_B1C_SRC ${CUSTOM_COMMON})

add_library(custom_b1c SHARED ${CUSTOM_B1C_SRC})

target_link_libraries(custom_b1c PUBLIC custom_signal)

target_include_directories(custom_b1c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(COPY custom_b1c_downlink.csv custom_b1c_data.xml custom_b1c_pilota.xml custom_b1c_pilotb.xml DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
