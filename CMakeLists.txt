cmake_minimum_required(VERSION 3.0.0)
project(run VERSION 1.0.0)

find_package(OpenGL REQUIRED)

add_executable(run
	src/config.h
	src/main.c
	src/glad.c
)

target_include_directories(run PRIVATE dependencies)

target_link_libraries(run m glfw OpenGL::GL)
