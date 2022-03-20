#lib&include set begin
set(THREADPOLL_LIB "thread_pool_lib" CACHE INTERNAL "thread_pool lib name")
set(THREADPOLL_DIR "${PROJECT_SOURCE_DIR}/thread_pool/include" CACHE INTERNAL "include dir path")

#export lib
add_library(${THREADPOLL_LIB} SHARED "src/thread_pool.cpp")

#lib&include set end
#add include directory
target_include_directories(${THREADPOLL_LIB} PRIVATE ${TEMPLATE_DIR})
target_include_directories(${THREADPOLL_LIB} PRIVATE ${COMMON_LIB})
target_include_directories(${THREADPOLL_LIB} PRIVATE ${THREADPOLL_DIR})

#add lib
target_link_libraries(${THREADPOLL_LIB} PRIVATE ${COMMON_LIB})