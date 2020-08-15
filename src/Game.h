#pragma once

#include "engine/gl/glad.h"
#include <GLFW/glfw3.h>
#include "engine/gl/Program.h"
#include "engine/gl/Texture2D.h"
#include "engine/Camera.h"
#include "engine/Model.h"
#include "engine/gl/Cubemap.h"

class Game {
    GLFWwindow *_window;

    bool _running;

    double _current_time;
    double _frame_timer;
    double _acc;
    double _t;
    int _frame_count;

    engine::gl::Program _program;
    engine::Model _model;

    engine::Camera _camera;
    double _mouse_x;
    double _mouse_y;
    bool _in_game;

    engine::gl::Cubemap _cubemap;

    void enter_game();
    void leave_game();
    void process_input();
    void update();
    void render();

    friend void framebuffer_size_callback(GLFWwindow *window, int width, int height);
public:
    Game(GLFWwindow *_window, const char *model_path);
    ~Game();
    void run();
};