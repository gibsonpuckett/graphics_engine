#include "main.h"
#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600

// TODO: Check for memory leaks
// TODO: change all the ints to lower level with minimum sizing, ie 16 bit etc.

int main()
{
  // STEP 0 :: INITIALIZE VARIABLES
  GLFWwindow* window_ptr = NULL; // Initialize pointers to NULL
  
  uint32_t VBO, EBO, VAO;
  int32_t success, nrAttributes;
  
  float vertices[] =
  {
     // positions         // colors
     0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top center
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // bottom left
  };

  uint32_t indices[] =
  { 
    0, 1, 2, // first triangle
  };
  
  float background_color[] = { 0.3f, 0.6f, 1.0f, 1.0f }; // RGBA

  // STEP 1 :: CREATE & INITIALIZE WINDOW
  make_window(&window_ptr, WIDTH, HEIGHT, background_color);

  // STEP 2 :: SETUP VERTICES / INDICES DATA
  setup_vertex_data(vertices, sizeof(vertices), indices, sizeof(indices), &VAO, &VBO, &EBO);
  
  // STEP 3 :: CREATE SHADER
  shader_t shader = shader_create(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

  // Main Loop
  while (!glfwWindowShouldClose(window_ptr)) {
    // Input
    process_input(window_ptr);

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Use correct shader program
    shader_use(&shader);
    shader_set_float(&shader, "someUniform", 1.0f); 

    // Draw to screen
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Check and call events and swap the buffers
    glfwSwapBuffers(window_ptr);
    glfwPollEvents();
  }

  // Upon termination
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  shader_destroy(&shader);
  glfwDestroyWindow(window_ptr);
  glfwTerminate();
  
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window_ptr, int32_t width, int32_t height)
{
  glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window_ptr)
{
  if(glfwGetKey(window_ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window_ptr, true);
}

void setup_vertex_data(
   float* vertices, size_t vert_size,
   uint32_t* indices, size_t index_size,
   uint32_t* vao_out, uint32_t* vbo_out, uint32_t* ebo_out)
{
  // VAO --> Vertex Array Object: Remembers how vertex data is laid out
  // VBO --> Vertex Buffer Object: Holds vertex data
  // EBO --> Element Buffer Object: Holds index data if reusing vertices

  // Generate and bind VAO
  glGenVertexArrays(1, vao_out);
  glBindVertexArray(*vao_out);

  // Generate and bind VBO
  glGenBuffers(1, vbo_out);
  glBindBuffer(GL_ARRAY_BUFFER, *vbo_out);
  glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);

  // Generate and bind EBO
  glGenBuffers(1, ebo_out);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo_out);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, indices, GL_STATIC_DRAW);

  // Describe vertex data layout
  const uint32_t stride = 6 * sizeof(float);

  // Vertex Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0); //(void*)0 --> index starts at 0 position
  glEnableVertexAttribArray(0);

  // Vertex Color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float))); // (void*)(3 * sizeof(float)) --> starts after first 3 floats
  glEnableVertexAttribArray(1);

  // Example //
  
  /* float vertices[] = */
  /* { */
  /*    // positions         // colors */
  /*    0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top center */
  /*    0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right */
  /*   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // bottom left */
  /* }; */

  /* unsigned int indices[] = */
  /* {  */
  /*   0, 1, 2, // first triangle */
  /* }; */

  // End Example //
}

int make_window(GLFWwindow** window_ptr, int32_t width, int32_t height, const float background_color[4])
{
  // Initialize GLFW Window
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create GLFW Window
  *window_ptr = glfwCreateWindow(width, height, "OpenGL Graphical Engine", NULL, NULL);
  if (!*window_ptr) {
    printf("Failed to create window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(*window_ptr);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD");
    glfwTerminate();
    return -1;
  }

  // Set screen color
  glClearColor(background_color[0], background_color[1], background_color[2], background_color[3]);

  // Tell OpenGL size of rendering window
  glViewport(0, 0, width, height);

  // Make rendering area resize when screen size is changed
  glfwSetFramebufferSizeCallback(*window_ptr, framebuffer_size_callback);

  return 0;
}
