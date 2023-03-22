cmake_minimum_required(VERSION 3.10)
project(shared_memory_example)

add_executable(shared_memory_example main.c)

FIND_LIBRARY(RT_LIBRARY rt)
message(${RT_LIBRARY})

IF(RT_LIBRARY)
    TARGET_LINK_LIBRARIES(shared_memory_example ${RT_LIBRARY})
ENDIF(RT_LIBRARY)

target_link_libraries(shared_memory_example rt)
