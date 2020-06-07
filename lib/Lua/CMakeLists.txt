include_directories(${CMAKE_CURRENT_SOURCE_DIR})

AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} source)

add_library(liblua ${source})
set_target_properties(liblua PROPERTIES OUTPUT_NAME "liblua")

# link /usr/include/lua5.3
add_library(liblua5.3 SHARED IMPORTED)

target_include_directories(liblua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
