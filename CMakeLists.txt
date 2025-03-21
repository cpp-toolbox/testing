cmake_minimum_required(VERSION 3.10)
project(testing)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB_RECURSE SOURCES "src/*.cpp")
# Add the main executable
add_executable(${PROJECT_NAME} ${SOURCES})


find_package(Catch2)
find_package(glm)
target_link_libraries(${PROJECT_NAME} Catch2::Catch2WithMain glm::glm)
