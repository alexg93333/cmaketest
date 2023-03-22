cmake_minimum_required(VERSION 3.10)
project(shared_memory_example)

add_executable(shared_memory_example main.c)

CHECK_LIBRARY_EXISTS(rt clock_gettime "time.h" NEED_LIBRT)
IF(NEED_LIBRT)
    message(need librt)
    TARGET_LINK_LIBRARIES(${target} rt)
    
target_link_libraries(shared_memory_example rt)
