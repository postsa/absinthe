#ifndef ABSINTHE_SQUARE_H
#define ABSINTHE_SQUARE_H

#include "Model.h"

namespace Models {

    class Square : Models::Model {

    public:
        Square();

        using Model::draw;
    };
}

#endif
