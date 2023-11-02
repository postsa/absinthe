//
// Created by Spencer Post on 11/1/23.
//

#include "Triangle.h"

namespace Models {

    Triangle::Triangle() {

        float v[] = {
                0.6f, 0.6f, 0.0f, // top right
                0.6f, -0.6f, 0.0f, // bottom right
                -0.6f, -0.6f, 0.0f, // bottom left
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

} // Models
