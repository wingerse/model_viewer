#include "Game.h"
#include "engine/stb_image.h"
#include <iostream>
#include <stdexcept>

constexpr int WINDOW_W = 1024;
constexpr int WINDOW_H = 800;

static void GLAPIENTRY
gl_error(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam )
{
    if (type != GL_DEBUG_TYPE_ERROR) return;
    std::cout << message << std::endl;
}

static void error_callback(int error, const char *desc)
{
    glfwTerminate();
    throw std::runtime_error{desc};
}

struct GLFW {
    GLFWwindow *_window;
    GLFW() 
    {
        glfwSetErrorCallback(error_callback);
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

        _window = glfwCreateWindow(WINDOW_W, WINDOW_H, "model_viewer", nullptr, nullptr);
        glfwMakeContextCurrent(_window);
        glfwSwapInterval(1);
        if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            throw std::runtime_error{"couldn't load opengl\n"};
        }

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(gl_error, nullptr);
    };
    
    ~GLFW()
    {
        glfwTerminate();
    }
};

int main(int argc, char** argv)
{
    const char *model_path;
    switch (argc) {
        case 1: model_path = "assets/pudge/pudge.obj"; break;
        case 2: model_path = argv[1]; break;
        default:
            std::cerr << "usage: model_viewer [model_path]";
            return 1;
    }

    std::ostream::sync_with_stdio(false);
    stbi_set_flip_vertically_on_load(true);

    GLFW glfw{};

    Game game{glfw._window, model_path};
    game.run();

    return 0;
}