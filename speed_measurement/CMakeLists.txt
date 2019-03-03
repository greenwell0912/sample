cmake_minimum_required (VERSION 2.6)
project (speed_measurement)
include_directories("${PROJECT_SOURCE_DIR}")
add_executable(speed_measurement main.c)
#target_link_libraries(speed_measurement socket)

# gcc -Wall オプションを指定する
set(CMAKE_C_FLAGS "-Wall -O3")
#set(CMAKE_C_FLAGS "-Wall")
