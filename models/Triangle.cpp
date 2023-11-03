#include "Triangle.h"

namespace Models {

    Triangle::Triangle() {

        float v[] = {
                0.6f, 0.6f, 0.0f,
                0.6f, -0.6f, 0.0f,
                -0.6f, -0.6f, 0.0f,
        };
        unsigned int i[] = {
                0, 1, 3,
        };

        vertices = v;
        indices = i;

        numberOfIndices = 3;
        numberOfVertices = 9;

        initialize();
    }

}
