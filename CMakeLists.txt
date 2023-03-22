project(shared_memory_example)


# Include the sys/mman.h header file
include(CheckIncludeFile)
check_include_file("sys/mman.h" HAVE_SYS_MMAN_H)
if (NOT HAVE_SYS_MMAN_H)
message(FATAL_ERROR "sys/mman.h not found")
endif()

FIND_LIBRARY(RT_LIBRARY c)
message(wwwwwww)
message(${RT_LIBRARY})

IF(RT_LIBRARY)
TARGET_LINK_LIBRARIES(shared_memory_example ${RT_LI>
ENDIF(RT_LIBRARY)

target_link_libraries(shared_memory_example rt)


add_executable(shared_memory_example main.c)
