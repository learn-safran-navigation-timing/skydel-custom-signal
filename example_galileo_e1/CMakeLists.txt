file(GLOB CUSTOM_E1_SRC *.cpp)

add_library(custom_e1 SHARED ${CUSTOM_E1_SRC})

target_link_libraries(custom_e1 PUBLIC custom_signal)

target_include_directories(custom_e1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(COPY custom_e1_downlink.csv custom_e1b.xml custom_e1c.xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
