set(COMMON_LIB "common_lib" CACHE INTERNAL "common library name")
set(COMMON_DIR "${PROJECT_SOURCE_DIR}/common/include" CACHE INTERNAL "common directory path")

add_library(${COMMON_LIB} SHARED "src/common.cpp")

target_include_directories(${COMMON_LIB} PRIVATE ${COMMON_DIR})