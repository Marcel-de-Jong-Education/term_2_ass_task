cmake_minimum_required(VERSION 3.10)
project(term_2)

set(CMAKE_CXX_STANDARD 11) # no explicit compiler flags if possible


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include_directories("${CMAKE_BINARY_DIR}/include/glad/include")

add_subdirectory("${CMAKE_BINARY_DIR}/include/glfw")

configure_file("${CMAKE_BINARY_DIR}/src/shaders/shader.vert" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
configure_file("${CMAKE_BINARY_DIR}/src/shaders/shader.frag" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


add_executable(term_2 "${CMAKE_BINARY_DIR}/src/main.cpp" "${CMAKE_BINARY_DIR}/include/glad/src/glad.c")
target_link_libraries(term_2 glfw)