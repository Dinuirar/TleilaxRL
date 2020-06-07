include_directories(${CMAKE_CURRENT_SOURCE_DIR})

AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} source)

add_library(librandom ${source})
set_target_properties(librandom PROPERTIES OUTPUT_NAME "librandom")

target_include_directories(librandom PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
