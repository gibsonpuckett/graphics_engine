#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* filePath)
{
  FILE* file = fopen(filePath, "r");
  if (!file)
    {
    fprintf(stderr, "Could not open shader file %s\n", filePath);
    return NULL;
    }

  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  rewind(file);

  // Temporarily malloc, eventually manually reserve memory
  char* content = (char*)malloc(length + 1);
  if (!content)
    {
    fprintf(stderr, "Memory allocation failed for shader file\n");
    fclose(file);
    return NULL;
    }

  fread(content, 1, length, file);
  content[length] = '\0';
  fclose(file);
  return content;
}

static unsigned int compile_shader(const char* source, GLenum type)
{
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  };

  return shader;

}
shader_t shader_create(const char* vertex_path, const char* fragment_path)
{
  shader_t shader;

  char* vertex_src = read_file(vertex_path);
  char* fragment_src = read_file(fragment_path);

  if (!vertex_src || !fragment_src)
    {
      shader.id = 0;
      return shader;
    }

  unsigned int vertex = compile_shader(vertex_src, GL_VERTEX_SHADER);
  unsigned int fragment = compile_shader(fragment_src, GL_FRAGMENT_SHADER);

  shader.id = glCreateProgram();
  glAttachShader(shader.id, vertex);
  glAttachShader(shader.id, fragment);
  glLinkProgram(shader.id);

  int success;
  char infoLog[512];
  glGetProgramiv(shader.id, GL_LINK_STATUS, &success);
  if (!success)
    {
      glGetProgramInfoLog(shader.id, 512, NULL, infoLog);
      fprintf(stderr, "ERROR::SHADER::LINKING_FAILED\n%s\n", infoLog);
    }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  free(vertex_src);
  free(fragment_src);

  return shader;

}

void shader_use(const shader_t* shader)
{
  glUseProgram(shader->id);
}

void shader_set_bool(const shader_t* shader, const char* name, bool value)
{
  glUniform1i(glGetUniformLocation(shader->id, name), (int)value);
}

void shader_set_int(const shader_t* shader, const char* name, int value)
{
  glUniform1i(glGetUniformLocation(shader->id, name), value);
}

void shader_set_float(const shader_t* shader, const char* name, float value)
{
  glUniform1f(glGetUniformLocation(shader->id, name), value);
}

void shader_destroy(shader_t* shader)
{
  glDeleteProgram(shader->id);
  shader->id = 0;
}
