include_directories(${CMAKE_CURRENT_SOURCE_DIR})

AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} source)

add_library(libtimeops ${source})
set_target_properties(libtimeops PROPERTIES OUTPUT_NAME "libtimeops")

target_include_directories(libtimeops PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
