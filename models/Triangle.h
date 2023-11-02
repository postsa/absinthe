#ifndef ABSINTHE_TRIANGLE_H
#define ABSINTHE_TRIANGLE_H

#include "Model.h"

namespace Models {

    class Triangle : Models::Model {
    public:
        Triangle();

        using Model::draw;
    };

}

#endif
