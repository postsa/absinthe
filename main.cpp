#include "SDL.h"
#include "SDL_video.h"
#include "OpenGL/gl.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "shaders/Program.h"
#include "shaders/Shader.h"
#include "models/Square.h"
#include "models/Triangle.h"
#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"
#include "models/OrientationWidget.h"
#include <iostream>

void rescale_framebuffer(float width, float height, GLuint renderBuffer, GLuint texture) {
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;


    SDL_Window *window = SDL_CreateWindow(
            "App",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL
    );

    auto gl = SDL_GL_CreateContext(window);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, gl);
    ImGui_ImplOpenGL3_Init("#version 120");

    bool show_debug_log = false;
    bool show_render = true;
    bool wireframeMode = false;


    GLuint texture;
    GLuint frameBuffer;
    GLuint renderBuffer;

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0
    );

    glGenRenderbuffers(1, &renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOW_WIDTH, WINDOW_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    Shaders::Shader vertexShader = Shaders::Shader("/Users/spence/Source/absinthe/shaders/glsl/vertex.glsl",
                                                   GL_VERTEX_SHADER);
    Shaders::Shader fragmentShader = Shaders::Shader("/Users/spence/Source/absinthe/shaders/glsl/fragment.glsl",
                                                     GL_FRAGMENT_SHADER);
    Shaders::Program shaderProgram = Shaders::Program(&vertexShader, &fragmentShader);

    Models::Square square1 = Models::Square();
    Models::OrientationWidget widget = Models::OrientationWidget();


    float cameraYaw = -90.0f;
    float cameraPitch = 0.0f;

    glm::vec3 cameraFront = glm::vec3(-1.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 cameraForward = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(-60.0f),
                        glm::vec3(1.0f, 0.0f, 0.0f));

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) 800 /
                                                           (float) 600, 0.1f, 100.0f);

    glm::vec3 direction;

    bool viewPortControls = false;

    SDL_Event e;
    bool quit = false;
    while (!quit) {

        const float cameraSpeed = 0.2f;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (!viewPortControls) {
                ImGui_ImplSDL2_ProcessEvent(&e);
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_v) {
                    viewPortControls = !viewPortControls;
                }
            }
            if (viewPortControls)
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        viewPortControls = false;
                    }
                    if (e.key.keysym.sym == SDLK_LEFT) {
                        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) *
                                     cameraSpeed;
                    }
                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) *
                                     cameraSpeed;
                    }
                    if (e.key.keysym.sym == SDLK_UP) {
                        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraForward)) *
                                     cameraSpeed;
                    }
                    if (e.key.keysym.sym == SDLK_DOWN) {
                        cameraPos += glm::normalize(glm::cross(cameraFront, cameraForward)) *
                                     cameraSpeed;
                    }
                    if (e.key.keysym.sym == SDLK_w) {
                        cameraPos += cameraUp * cameraSpeed;
                    }
                    if (e.key.keysym.sym == SDLK_s) {
                        cameraPos -= cameraUp * cameraSpeed;
                    }
                }
        }

        direction.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
        direction.z = sin(glm::radians(cameraYaw) * cos(glm::radians(cameraPitch)));
        direction.y = sin(glm::radians(cameraPitch));
        cameraFront = glm::normalize(direction);

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        if (ImGui::GetIO().KeyAlt)
            printf("");

        static int counter = 0;
        static float positionDiag = 0.0f;
        static float rColor = 0.5f;
        static float gColor = 0.5f;
        static float bColor = 0.5f;

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Begin("Control");
        ImGui::Checkbox("Show Debug Log", &show_debug_log);
        ImGui::Checkbox("Show Render", &show_render);
        ImGui::Checkbox("Wireframe Mode", &wireframeMode);
        ImGui::Checkbox("Control View Port", &viewPortControls);
        ImGui::SliderFloat("Position", &positionDiag, -1.0f, 1.0f);
        ImGui::SliderFloat("R Value", &rColor, 0.0f, 1.0f);
        ImGui::SliderFloat("G Value", &gColor, 0.0f, 1.0f);
        ImGui::SliderFloat("B Value", &bColor, 0.0f, 1.0f);

        if (ImGui::Button("Button"))
            counter++;

        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::End();

        int renderMode = GL_FILL;
        if (wireframeMode) {
            renderMode = GL_LINE;
        }

        glPolygonMode(GL_FRONT_AND_BACK,
                      renderMode);

        if (show_debug_log) {
            ImGui::ShowDebugLogWindow();
        }


        if (show_render) {

            ImGui::Begin("Camera Info");
            ImGui::Text("Displays information about the camera");
            ImGui::Text("X position %f", cameraPos.x);
            ImGui::Text("Y position %f", cameraPos.y);
            ImGui::Text("Z position %f", cameraPos.z);
            ImGui::Text("Yaw %f", cameraYaw);
            ImGui::Text("Pitch %f", cameraPitch);
            ImGui::End();
            ImGui::Begin("Viewport");
            const float window_width = ImGui::GetContentRegionAvail().x;
            const float window_height = ImGui::GetContentRegionAvail().y;
            rescale_framebuffer(window_width, window_height, renderBuffer, texture);
            proj = glm::perspective(glm::radians(45.0f), (float) window_width /
                                                         (float) window_height, 0.1f, 100.0f);

            glViewport(0, 0, window_width, window_height);
            ImVec2 wsize = ImGui::GetWindowSize();
            ImGui::Image((ImTextureID) texture, wsize, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::End();
        }

        ImGui::Render();

        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.use();
        shaderProgram.setFloat("tintAmount", 0.5f);
        shaderProgram.setMatrix("model", model);
        shaderProgram.setMatrix("view", view);
        shaderProgram.setMatrix("projection", proj);

        glColor3f(rColor, gColor, bColor);

        // RENDER HERE
        square1.draw();
        widget.draw();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    glDeleteFramebuffers(1, &frameBuffer);
    ImGui_ImplSDL2_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}