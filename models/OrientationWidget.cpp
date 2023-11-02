#include "OrientationWidget.h"
#include "OpenGL/gl.h"

namespace Models {
    OrientationWidget::OrientationWidget() {
        drawMode = GL_LINES;

        float v[] = {
                -1.0f, -1.0f, 0.0f,
                -0.5f, -1.0f, 0.0f,
                -1.0f, -0.5f, 0.0f,
                -1.0f, -1.0f, 0.5f
        };
        unsigned int i[] = {
                0, 1, 0, 2, 0, 3
        };

        vertices = v;
        indices = i;

        numberOfIndices = 6;
        numberOfVertices = 12;

        initialize();
    }
}