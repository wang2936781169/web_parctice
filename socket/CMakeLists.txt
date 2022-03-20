#lib&include set begin
set(SOCKET_LIB "socket_lib" CACHE INTERNAL "socket lib name")
set(SOCK_DIR "${PROJECT_SOURCE_DIR}/socket/include" CACHE INTERNAL "include dir path")
#lib&include set end

#export lib
add_library(${SOCKET_LIB} SHARED "src/socket.cpp")

#add include directory
target_include_directories(${SOCKET_LIB} PRIVATE ${COMMON_DIR})
target_include_directories(${SOCKET_LIB} PRIVATE ${SOCK_DIR})

#add lib
target_link_libraries(${SOCKET_LIB} PRIVATE ${COMMON_LIB})