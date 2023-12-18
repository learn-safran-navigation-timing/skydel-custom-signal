file(GLOB CUSTOM_QZSS_CA *.cpp)
file(GLOB CUSTOM_COMMON "../common/*.cpp")
list(APPEND CUSTOM_QZSS_CA ${CUSTOM_COMMON})

add_library(custom_qzss_ca SHARED ${CUSTOM_QZSS_CA})
add_library(custom_qzss_ca_static STATIC ${CUSTOM_QZSS_CA})

target_link_libraries(custom_qzss_ca PUBLIC custom_signal)
target_link_libraries(custom_qzss_ca_static PUBLIC custom_signal)

target_include_directories(custom_qzss_ca PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(custom_qzss_ca_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(custom_qzss_ca_static PRIVATE IS_STATIC)

file(COPY custom_qzss_ca_downlink.csv custom_qzss_ca.xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
