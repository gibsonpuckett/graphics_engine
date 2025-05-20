#include "main.h"
#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600

int main()
{
  // Initialize Variables
  GLFWwindow* window;
  unsigned int VBO, EBO, VAO, vertexShader, fragmentShader, shaderProgram;
  int success, nrAttributes;
  char infoLog[512];

  float vertices[] =
  {
     // positions         // colors
     0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top center
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // bottom left
  };

  unsigned int indices[] =
  { 
    0, 1, 2, // first triangle
  };

  // Initialize GLFW Window
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create GLFW Window
  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Graphical Engine", NULL, NULL);
  if (!window)
  {
    printf("Failed to create window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD");
    glfwTerminate();
    return -1;
  }

  // Set screen color
  glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

  // Tell OpenGL size of rendering window (and resizable screen)
  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Set buffers for VBO and EBO
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Create Shaders
  shader_t shader = shader_create(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
  
  // 1. Generate and bind vertex array object
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // 2. Copy vertices array in a buffer for OpenGL to use
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // 3. Set the vertex attributes pointers
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  //4. Set the vertex attributes pointers
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // 5. Draw the object in render loop
    
  // Wireframe mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  //glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  //printf("Maximum number of vertex attributes supported: %d \n", nrAttributes);
  glUseProgram(shaderProgram);

  // 
  // Main Loop
  while (!glfwWindowShouldClose(window))
  {
    // Input
    processInput(window);

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Use correct shader program
    shader_use(&shader);
    shader_set_float(&shader, "someUniform", 1.0f); 

    // Draw to screen
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Upon termination
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  shader_destroy(&shader);
  glfwDestroyWindow(window);

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
