cmake_minimum_required(VERSION 3.10)
project(term_2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create GLAD library directly
add_library(glad STATIC
    "${PROJECT_SOURCE_DIR}/dep/glThings/dep/glad/src/glad.c"
    "${PROJECT_SOURCE_DIR}/dep/glThings/dep/glad/include/glad/glad.h"
)

# Set include directory for GLAD
target_include_directories(glad PUBLIC
    "${PROJECT_SOURCE_DIR}/dep/glThings/dep/glad/include"
)

# Add GLFW subdirectory
add_subdirectory(dep/glThings/dep/glfw)

# Add GLM subdirectory
add_subdirectory(dep/glThings/dep/glm)

# Create the executable
add_executable(${PROJECT_NAME} "./src/main.cpp")

# Link all dependencies
target_link_libraries(${PROJECT_NAME}
    PRIVATE glad
    PRIVATE glfw
    PRIVATE glm::glm
)

# Set up include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}/dep/glThings/include"
    "${PROJECT_SOURCE_DIR}/dep/glThings/src"  # Added this line
    "${PROJECT_BINARY_DIR}/src"
    "${PROJECT_SOURCE_DIR}/dep/glThings/dep/glad/include"
    "${PROJECT_SOURCE_DIR}/dep/glThings/dep/glfw/include"
    "${PROJECT_SOURCE_DIR}/dep/glThings/dep/glm"
)