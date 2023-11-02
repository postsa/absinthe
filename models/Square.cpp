#include "Square.h"

#include "OpenGL/gl.h"

namespace Models {
    Square::Square() {
        float v[] = {
                0.5f, 0.5f, 0.0f, // top right
                0.5f, -0.5f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f, // bottom left
                -0.5f, 0.5f, 0.0f // top left
        };
        unsigned int i[] = { // note that we start from 0!
                0, 1, 3, // first triangle
                1, 2, 3 // second triangle
        };

        vertices = v;
        indices = i;

        numberOfIndices = 6;
        numberOfVertices = 12;

        initialize();
    }
}
