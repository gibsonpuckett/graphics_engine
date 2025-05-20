#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Resize render window when window gets resized
void framebuffer_size_callback(GLFWwindow* window_ptr, int32_t width, int32_t height);

// Escape program on ESC key pressed
void process_input(GLFWwindow* window_ptr);

// Setup the vertex data
void setup_vertex_data(float* vertices, size_t vert_size,
		       uint32_t* indices, size_t index_size,
		       uint32_t* vao_out, uint32_t* vbo_out, uint32_t* ebo_out);

// Make a window and initialize it
int make_window(GLFWwindow** window_ptr, int32_t width, int32_t height, const float background_color[4]);

