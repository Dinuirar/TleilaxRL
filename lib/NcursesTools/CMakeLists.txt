include_directories(${CMAKE_CURRENT_SOURCE_DIR})

AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} source)

add_library(libncursestools ${source})
set_target_properties(libncursestools PROPERTIES OUTPUT_NAME "libncursestools")

target_include_directories(libncursestools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
