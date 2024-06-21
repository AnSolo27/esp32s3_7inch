FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/main/*.* ${CMAKE_SOURCE_DIR}/main/ui/*.*)

FILE(GLOB_RECURSE lvgl_src ${CMAKE_SOURCE_DIR}/main/lvgl/src/ui/*.*)

idf_component_register(SRCS ${app_sources} ${lvgl_src} INCLUDE_DIRS "inc/")

