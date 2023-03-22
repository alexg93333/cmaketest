cmake_minimum_required(VERSION 3.10)
project(shared_memory_example)

add_executable(shared_memory_example main.c)

link_directories(/data/user/0/com.termux/files/usr/lib/)

target_link_libraries(shared_memory_example rt)