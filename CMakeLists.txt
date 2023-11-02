cmake_minimum_required(VERSION 3.26)
project(absinthe)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} imgui)

add_executable(
        absinthe
        imgui/imgui.h
        imgui/imconfig.h
        imgui/imgui_internal.h
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        imgui/imgui_impl_sdl2.h
        imgui/imgui_impl_sdl2.cpp
        imgui/imgui_impl_opengl3.cpp
        imgui/imgui_impl_opengl3.h
        imgui/imgui_demo.cpp
        main.cpp
        shaders/Shader.cpp
        shaders/Shader.h
        shaders/Program.cpp
        shaders/Program.h
        models/Square.cpp
        models/Square.h
        models/Triangle.cpp
        models/Triangle.h
        models/Model.cpp
        models/Model.h
        models/OrientationWidget.cpp
        models/OrientationWidget.h
)

target_link_libraries(absinthe ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})

