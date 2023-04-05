#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include "shaders.h"

void Shader::use()
{
    glUseProgram(id);
}

void Shader::sendUniform1i(const std::string local, int value)
{
    glUniform1i(glGetUniformLocation(id, local.c_str()), value);
}

void Shader::sendUniform2i(const std::string local, int value1, int value2)
{
    glUniform2i(glGetUniformLocation(id, local.c_str()), value1, value2);
}

void Shader::sendUniform3i(const std::string local, int value1, int value2, int value3)
{
    glUniform3i(glGetUniformLocation(id, local.c_str()), value1, value2, value3);
}

void Shader::sendUniform4i(const std::string local, int value1, int value2, int value3, int value4)
{
    glUniform4i(glGetUniformLocation(id, local.c_str()), value1, value2, value3, value4);
}

void Shader::sendUniformiv(const std::string local, int *value, size_t size)
{
    glUniform1iv(glGetUniformLocation(id, local.c_str()), size, value);
}

void Shader::sendUniform1f(const std::string local, float value)
{
    glUniform1f(glGetUniformLocation(id, local.c_str()), value);
}

void Shader::sendUniform2f(const std::string local, float value1, float value2)
{
    glUniform2f(glGetUniformLocation(id, local.c_str()), value1, value2);
}

void Shader::sendUniform3f(const std::string local, float value1, float value2, float value3)
{
    glUniform3f(glGetUniformLocation(id, local.c_str()), value1, value2, value3);
}

void Shader::sendUniform4f(const std::string local, float value1, float value2, float value3, float value4)
{
    glUniform4f(glGetUniformLocation(id, local.c_str()), value1, value2, value3, value4);
}

void Shader::sendUniformfv(const std::string local, float *value, size_t size)
{
    glUniform1fv(glGetUniformLocation(id, local.c_str()), size, value);
}

void Shader::sendUniformMat4(const std::string local, const glm::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(id, local.c_str()), 1, false, glm::value_ptr(matrix));
}
