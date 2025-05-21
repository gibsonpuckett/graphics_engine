cmake_minimum_required(VERSION 3.10)
project(run C)

set(CMAKE_C_STANDARD 99)

# Add subdirectories (cglm, glfw)
add_subdirectory(dependencies/cglm)
add_subdirectory(dependencies/glfw)

# Find system OpenGL
find_package(OpenGL REQUIRED)

# Executable
add_executable(run
  src/main.c
  src/shader.c
  src/noise.c
  src/bmp_loader.c

  dependencies/glad/src/glad.c
)

# Include directories
target_include_directories(run PRIVATE
  include
  dependencies/glad/include
  dependencies/glfw/include
  dependencies/cglm/include
)

# Link libraries
target_link_libraries(run PRIVATE
  m
  glfw
  cglm
  OpenGL::GL
)
