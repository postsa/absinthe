//
// Created by Spencer Post on 11/1/23.
//

#ifndef ABSINTHE_MODEL_H
#define ABSINTHE_MODEL_H

namespace Models {

    class Model {
    protected:
        unsigned int drawMode;
        float *vertices;
        unsigned int *indices;
        unsigned int numberOfVertices;
        unsigned int numberOfIndices;
        unsigned int vertexArrayObject;
        unsigned int vertexBufferObject;
        unsigned int elementBufferObject;

        Model();

        void initialize();

    public:
        void draw();
    };

} // Models

#endif //ABSINTHE_MODEL_H
