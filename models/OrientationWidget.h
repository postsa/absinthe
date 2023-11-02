//
// Created by Spencer Post on 11/1/23.
//

#ifndef ABSINTHE_ORIENTATIONWIDGET_H
#define ABSINTHE_ORIENTATIONWIDGET_H

#include "Model.h"

namespace Models {

    class OrientationWidget : Models::Model {
    public:
        OrientationWidget();

        using Model::draw;
    };

} // Models

#endif //ABSINTHE_ORIENTATIONWIDGET_H
