#cmake minimun required begin
cmake_minimum_required(VERSION 3.1)
#cmake minimun required end

#variable set begin
set(PRJ_NAME "web_practice")
set(COMMON "./common")
set(SOCKET "./socket")
set(THREAD_POOL "./thread_pool")
set(TEMPLATE "./template")
set(TEST_PARAM "test dir" CACHE INTERNAL "test dir description")
#variable set end

#project set begin
project(${PRJ_NAME})
add_compile_options(-g -std=c++17 -Wall)
#project set end

#sub directory add begin
add_subdirectory(${COMMON})
add_subdirectory(${TEMPLATE})
add_subdirectory(${THREAD_POOL})
add_subdirectory(${SOCKET})
#sub directory add end

#exec export begin
add_executable(${PRJ_NAME} main.cpp)
#exec export end

#macro begin
add_definitions(-DThreadReturn)
#macro end

#package include begin
target_include_directories(${PRJ_NAME} PRIVATE ${COMMON_DIR})
target_include_directories(${PRJ_NAME} PRIVATE ${TEMPLATE_DIR})
target_include_directories(${PRJ_NAME} PRIVATE ${SOCK_DIR})
target_include_directories(${PRJ_NAME} PRIVATE ${THREADPOLL_DIR})
#package include end

#lib add begin
target_link_libraries(${PRJ_NAME} PRIVATE ${COMMON_LIB})
target_link_libraries(${PRJ_NAME} PRIVATE ${SOCKET_LIB})
target_link_libraries(${PRJ_NAME} PRIVATE ${THREADPOLL_LIB})
#lib add end