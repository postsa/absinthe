#include "Model.h"
#include "OpenGL/gl.h"

namespace Models {

    Model::Model() {
        drawMode = GL_TRIANGLES;
    }

    void Model::initialize() {

        glGenBuffers(1, &elementBufferObject);

        glGenVertexArraysAPPLE(1, &vertexArrayObject);
        glGenBuffers(1, &vertexBufferObject);

        glBindVertexArrayAPPLE(vertexArrayObject);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);


        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numberOfIndices, indices,
                     GL_STATIC_DRAW);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfVertices, vertices, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArrayAPPLE(0);
    }

    void Model::draw() {
        glBindVertexArrayAPPLE(vertexArrayObject);
        glDrawElements(drawMode, numberOfIndices, GL_UNSIGNED_INT, 0);
        glDrawElements(drawMode, numberOfIndices, GL_UNSIGNED_INT, 0);
        glBindVertexArrayAPPLE(0);
    }
} // Models