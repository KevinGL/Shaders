#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "../glm/glm.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

class Shader
{
    private :

    GLuint id;

    char* loadFile(const std::string path);
    bool checkCompil(GLuint program, const std::string path);
    bool checkLink(GLuint program);
    std::string includeFile(const std::string line, const std::string shaderPath);

    public :

    bool Load(const std::string path);
    void use();

    void sendUniform1i(const std::string local, int value);
    void sendUniform2i(const std::string local, int value1, int value2);
    void sendUniform3i(const std::string local, int value1, int value2, int value3);
    void sendUniform4i(const std::string local, int value1, int value2, int value3, int value4);
    void sendUniformiv(const std::string local, int *value, size_t size);

    void sendUniform1f(const std::string local, float value);
    void sendUniform2f(const std::string local, float value1, float value2);
    void sendUniform3f(const std::string local, float value1, float value2, float value3);
    void sendUniform4f(const std::string local, float value1, float value2, float value3, float value4);
    void sendUniformfv(const std::string local, float *value, size_t size);

    void sendUniformMat4(const std::string local, const glm::mat4 matrix);

    GLuint getId()
    {
        return id;
    }
};
