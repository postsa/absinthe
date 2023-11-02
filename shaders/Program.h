#ifndef ABSINTHE_PROGRAM_H
#define ABSINTHE_PROGRAM_H

#include "Shader.h"
#include <string>
#include "../includes/glm/glm.hpp"

using namespace std;

namespace Shaders {

    class Program {
        unsigned int Id;

    public:
        Program(Shader *vertexShader, Shader *fragmentShader);

        void use();

        void setBool(const string &name, bool value) const;

        void setInt(const string &name, int value) const;

        void setFloat(const string &name, float value) const;

        void setMatrix(const string &name, glm::mat4 value);
    };

}

#endif
