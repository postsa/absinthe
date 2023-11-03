#include "Square.h"

#include "OpenGL/gl.h"

namespace Models {
    Square::Square() {
        float v[] = {
                0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f
        };
        unsigned int i[] = {
                0, 1, 3,
                1, 2, 3
        };

        vertices = v;
        indices = i;

        numberOfIndices = 6;
        numberOfVertices = 12;

        initialize();
    }
}
