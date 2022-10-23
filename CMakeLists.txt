cmake_minimum_required (VERSION 3.10)

project(
    RobotSwarmManager
)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB _srcs "src/*")
add_library(RobotSwarmManager ${_srcs})
add_executable(main main.cpp)
target_link_libraries(main RobotSwarmManager)
