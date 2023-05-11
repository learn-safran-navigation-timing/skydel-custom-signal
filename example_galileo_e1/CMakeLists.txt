file(GLOB CUSTOM_E1_SRC *.cpp)
file(GLOB CUSTOM_COMMON "../common/*.cpp")
list(APPEND CUSTOM_E1_SRC ${CUSTOM_COMMON})

add_library(custom_e1 SHARED ${CUSTOM_E1_SRC})
add_library(custom_e1_static STATIC ${CUSTOM_E1_SRC})

target_link_libraries(custom_e1 PUBLIC custom_signal)
target_link_libraries(custom_e1_static PUBLIC custom_signal)

target_include_directories(custom_e1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(custom_e1_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(custom_e1_static PRIVATE IS_STATIC)

file(COPY custom_e1_downlink.csv custom_e1b.xml custom_e1c.xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
