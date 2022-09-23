file(GLOB CUSTOM_CA_SRC *.cpp)

add_library(custom_ca SHARED ${CUSTOM_CA_SRC})

target_link_libraries(custom_ca PUBLIC custom_signal)

target_include_directories(custom_ca PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(COPY custom_ca_downlink.csv custom_ca.xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
