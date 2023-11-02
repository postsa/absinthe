#include "Program.h"
#include <iostream>
#include <OpenGL/gl.h>
#include "Shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

const int BUFFER_SIZE = 512;

using namespace std;


namespace Shaders {
    Program::Program(Shader *vertexShader, Shader *fragmentShader) {
        Id = glCreateProgram();

        int success;
        char infoLog[BUFFER_SIZE];

        glAttachShader(Id, vertexShader->id);
        glAttachShader(Id, fragmentShader->id);
        glLinkProgram(Id);
        glGetProgramiv(Id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(Id, BUFFER_SIZE, NULL, infoLog);
            cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
                 infoLog << endl;
        }
        vertexShader->deleteShader();
        fragmentShader->deleteShader();
    }

    void Program::use() {
        glUseProgram(Id);
    }

    void Program::setBool(const string &name, bool value) const {
        glUniform1i(glGetUniformLocation(Id, name.c_str()), (int) value);
    }

    void Program::setInt(const string &name, int value) const {
        glUniform1i(glGetUniformLocation(Id, name.c_str()), value);
    }

    void Program::setFloat(const string &name, float value) const {
        glUniform1f(glGetUniformLocation(Id, name.c_str()), value);
    }

    void Program::setMatrix(const string &name, glm::mat4 value) {
        int location = glGetUniformLocation(Id, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
}