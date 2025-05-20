#pragma once
#include <glad/glad.h>
#include <stdbool.h>

#define SHADER_DIR "../assets/shaders/"
#define VERTEX_SHADER_PATH "../assets/shaders/vertex_shader.glsl"
#define FRAGMENT_SHADER_PATH "../assets/shaders/fragment_shader.glsl"

// Represent a shader program as a component in ECS
typedef struct {
  GLuint id;
} shader_t;

// Create a shader from vertex and fragment source files
shader_t shader_create(const char* vertex_path, const char* fragment_path);

// Activate the shader
void shader_use(const shader_t* shader);

// Uniform setters
void shader_set_bool(const shader_t* shader, const char* name, bool value);
void shader_set_int(const shader_t* shader, const char* name, int32_t value);
void shader_set_float(const shader_t* shader, const char* name, float value);

// Delete shader program when no longer needed
void shader_destroy(shader_t* shader);

