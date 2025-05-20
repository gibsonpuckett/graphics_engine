cmake_minimum_required(VERSION 3.0.0)
project(run VERSION 1.0.0)

find_package(OpenGL REQUIRED)

add_executable(run
	src/main.c
	src/glad.c
	src/shader.c
)

target_include_directories(run PRIVATE dependencies include assets)

target_link_libraries(run m glfw OpenGL::GL)
