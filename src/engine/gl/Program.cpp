#include "Program.h"
#include <memory>
#include <array>
#include <sstream>

namespace engine::gl {

class Shader {
    GLuint _id;

public:
    GLuint id() const { return _id; }

    Shader(GLint type, const char *source) 
        : _id{glCreateShader(type)}
    {
        glShaderSource(_id, 1, &source, nullptr);
        glCompileShader(_id);

        GLint success;
        glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLint length;
            glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length);
            auto info_log = std::unique_ptr<char[]>(new char[length]);
            glGetShaderInfoLog(_id, static_cast<GLsizei>(length), nullptr, info_log.get());
            throw std::runtime_error { info_log.get() };
        }
    }

    ~Shader() 
    {
        if (_id) {
            glDeleteShader(_id);
        }
    }

    Shader(Shader&& s) noexcept
        : _id{s._id}
    {
        s._id = 0;
    }

    Shader& operator=(Shader s) 
    {
        std::swap(_id, s._id);
        return *this;
    }
};

Program::Program(const char *vertex_src, const char *fragment_src)
    : _id(glCreateProgram())
{
    auto vertex = Shader{GL_VERTEX_SHADER, vertex_src};
    auto fragment = Shader{GL_FRAGMENT_SHADER, fragment_src};
    glAttachShader(_id, vertex.id());
    glAttachShader(_id, fragment.id());

    glLinkProgram(_id);
    GLint success;
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success) {
        GLint length;
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);
        auto info_log = std::unique_ptr<char[]>(new char[length]);
        glGetProgramInfoLog(_id, static_cast<GLsizei>(length), nullptr, info_log.get());
        throw std::runtime_error{info_log.get()};
    }

    glDetachShader(_id, vertex.id());
    glDetachShader(_id, fragment.id());
}

Program::~Program()
{
    if (_id) {
        glDeleteProgram(_id);
    }
}

Program::Program(Program&& p) noexcept
    : _id{p._id}
{
    p._id = 0;
}

Program& Program::operator=(Program p)
{
    std::swap(_id, p._id);
    return *this;
}

void Program::use() const
{
    glUseProgram(_id);
}

GLint Program::get_uniform_location(const char *name) const
{
    GLint l = glGetUniformLocation(_id, name);
    std::ostringstream s {};
    s << "invalid uniform: " << name;
    if (l == -1) throw std::runtime_error{s.str()};
    return l;
}

void Program::set_uniform(const char *name, math::vec4 vec) const
{
    glUniform4f(get_uniform_location(name), vec.x(), vec.y(), vec.z(), vec.w());
}

void Program::set_uniform(const char *name, math::vec3 vec) const
{
    glUniform3f(get_uniform_location(name), vec.x(), vec.y(), vec.z());
}

void Program::set_uniform(const char *name, const math::mat4& mat) const
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_TRUE, &mat[0][0]);
}

void Program::set_uniform(const char *name, GLint i) const
{
    glUniform1i(get_uniform_location(name), i);
}

void Program::set_uniform(const char *name, GLfloat f) const
{
    glUniform1f(get_uniform_location(name), f);
}

}