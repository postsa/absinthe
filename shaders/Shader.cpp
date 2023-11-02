#include "Shader.h"
#include "OpenGL/gl.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

const int BUFFER_SIZE = 512;

using namespace std;

namespace Shaders {
    Shader::Shader(const char *path, GLenum type) {
        string code;
        ifstream shaderFile;

        shaderFile.exceptions(ifstream::failbit | ifstream::badbit);
        try {
            shaderFile.open(path);
            stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            code = shaderStream.str();
        }
        catch (ifstream::failure &e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        }

        const char *shaderCode = code.c_str();
        int success;
        char infoLog[BUFFER_SIZE];
        id = glCreateShader(type);
        glShaderSource(id, 1, &shaderCode, NULL);
        glCompileShader(id);
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id, BUFFER_SIZE, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
                      infoLog << std::endl;
        };
    }


    void Shader::deleteShader() const {
        glDeleteShader(id);
    }
}
