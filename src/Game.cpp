#include "Game.h"
#include <iostream>
#include <memory>
#include <array>
#include <string>
#include <exception>
#include "math/math.h"

using namespace engine::gl;
using namespace math;

constexpr int TICKS_PER_FRAME = 60;
constexpr float dt = 1.0f/TICKS_PER_FRAME;

constexpr auto vertex_src = R"glsl(
    #version 460 core
    layout (location=0) in vec3 pos;
    layout (location=1) in vec3 normal;
    layout (location=2) in vec2 tex_coord;

    out vec3 _frag_pos;
    out vec3 _normal;
    out vec2 _tex_coord;

    uniform mat4 modelview;
    uniform mat4 proj;
    uniform mat4 normal_matrix;

    void main() 
    { 
        _frag_pos = vec3(modelview * vec4(pos, 1));
        _normal = vec3(normal_matrix * vec4(normal, 1.0));
        _tex_coord = tex_coord;
        gl_Position = proj * modelview * vec4(pos, 1.0);
    }
)glsl";

constexpr auto fragment_src = R"glsl(
    #version 460 core
    out vec4 color;

    in vec3 _frag_pos;
    in vec3 _normal;
    in vec2 _tex_coord;

    struct Material {
        sampler2D diffuse;
        sampler2D specular;
        float shininess;
    };

    uniform vec3 light_pos;
    uniform Material material;

    void main() 
    { 
        vec4 pixel = texture(material.diffuse, _tex_coord);
        vec3 normal = normalize(_normal);

        vec4 ambient = 0.05 * pixel;

        vec3 light_dir = normalize(light_pos - _frag_pos);
        float diffuse_str = max(dot(light_dir, normal), 0);
        vec4 diffuse = diffuse_str * pixel;

        vec3 reflected = reflect(-light_dir, normal);
        vec3 eye_dir = normalize(-_frag_pos);
        float specular_str = max(dot(reflected, eye_dir), 0);
        specular_str = pow(specular_str, material.shininess);
        vec4 specular = specular_str * texture(material.specular, _tex_coord);
        
        color = vec4(vec3(ambient+diffuse+specular), 1.0);
    }
)glsl";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    Game* g = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
    g->_camera.set_proj_matrix(perspective(45, static_cast<float>(width)/static_cast<float>(height), 0.1f, 100));
}

Game::Game(GLFWwindow* window, const char *model_path)
    : _window{window}
    , _running{true}
    , _program{vertex_src, fragment_src}
    , _model{model_path}
    , _camera{
        identity,  // will be set in framebuffer_size_callback
        vec3{0, 0, 0},
        0, 0
    }
    , _cubemap({"assets/skybox/right.jpg", "assets/skybox/left.jpg", "assets/skybox/top.jpg", "assets/skybox/bottom.jpg",
                "assets/skybox/front.jpg", "assets/skybox/back.jpg"})
{
    glfwSetWindowUserPointer(_window, this);

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);
    framebuffer_size_callback(_window, width, height);

    enter_game();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);

    glClearColor(0, 0, 0, 1);
}

Game::~Game()
{
}

void Game::enter_game()
{
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(_window, &_mouse_x, &_mouse_y);
    _in_game = true;
}

void Game::leave_game()
{
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    _in_game = false;
}

void Game::run()
{
    _current_time = glfwGetTime();
    _frame_timer = 0.0;
    _acc = 0.0;
    _t = 0;
    _frame_count = 0;

    while (_running) {
        double new_time = glfwGetTime();
        double frame_time = new_time-_current_time;
        _current_time = new_time;
        _frame_timer += frame_time;
        _t += frame_time;
        if (frame_time>0.25) frame_time = 0.25;

        if (_frame_timer>=2.0) {
            std::cout << _frame_count/2.0 << std::endl;
            _frame_timer = 0.0;
            _frame_count = 0;
        }

        _acc += frame_time;

        while (_acc>=dt) {
            process_input();
            update();
            _acc -= dt;
        }

        render();
        _frame_count++;
    }
}

void Game::process_input()
{
    glfwPollEvents();

    if (glfwWindowShouldClose(_window)) {
        _running = false;
        return;
    }

    if (glfwGetKey(_window, GLFW_KEY_ESCAPE)) {
        leave_game();
    }
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_1)) {
        enter_game();
    }

    if (!_in_game) return;

    constexpr float speed = 2*dt;

    if (glfwGetKey(_window, GLFW_KEY_W)) _camera.move_forward(speed);
    if (glfwGetKey(_window, GLFW_KEY_S)) _camera.move_backward(speed);
    if (glfwGetKey(_window, GLFW_KEY_A)) _camera.move_left(speed);
    if (glfwGetKey(_window, GLFW_KEY_D)) _camera.move_right(speed);
    if (glfwGetKey(_window, GLFW_KEY_SPACE)) _camera.move_up(speed);
    if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT)) _camera.move_down(speed);

    double prev_mouse_x = _mouse_x;
    double prev_mouse_y = _mouse_y;
    glfwGetCursorPos(_window, &_mouse_x, &_mouse_y);
    double mouse_x_offset = (_mouse_x-prev_mouse_x);
    double mouse_y_offset = -(_mouse_y-prev_mouse_y);
    constexpr double sensitivity = 15*dt;
    mouse_x_offset *= sensitivity;
    mouse_y_offset *= sensitivity;
    float yaw = _camera.yaw();
    float pitch = _camera.pitch();
    yaw += static_cast<float>(mouse_x_offset);
    pitch += static_cast<float>(mouse_y_offset);
    _camera.set_yaw_pitch(yaw, pitch);

    _camera.update_view_matrix();
}

void Game::update()
{
}

void Game::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _program.use();
    mat4 model = identity;
    mat4 view = _camera.view_matrix();
    mat4 proj = _camera.proj_matrix();
    _program.set_uniform("light_pos", vec3(view*vec4(5, 5, 5, 1)));
    _model.draw(_program, model, view, proj);
    _cubemap.draw(view, proj);
    glfwSwapBuffers(_window);
}