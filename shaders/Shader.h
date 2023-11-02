#ifndef ABSINTHE_SHADER_H
#define ABSINTHE_SHADER_H

#include "OpenGL/gl.h"

namespace Shaders {
    class Shader {

    public:
        unsigned int id;

        Shader(const char *path, GLenum type);

        void deleteShader() const;

    };
}

#endif
