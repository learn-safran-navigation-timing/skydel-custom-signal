file(GLOB CUSTOM_TDDM_CA_SRC *.cpp)
file(GLOB CUSTOM_COMMON "../common/*.cpp")
list(APPEND CUSTOM_TDDM_CA_SRC ${CUSTOM_COMMON})

add_library(custom_tddm_ca SHARED ${CUSTOM_TDDM_CA_SRC})
add_library(custom_tddm_ca_static STATIC ${CUSTOM_TDDM_CA_SRC})

target_link_libraries(custom_tddm_ca PUBLIC custom_signal)
target_link_libraries(custom_tddm_ca_static PUBLIC custom_signal)

target_include_directories(custom_tddm_ca PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(custom_tddm_ca_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(custom_tddm_ca_static PRIVATE IS_STATIC)

file(COPY custom_tddm_ca_downlink.csv custom_tddm_ca.xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
