#pragma once

#include "glad.h"

namespace engine::gl {

class VAO {
    GLuint _id;
    bool _moved;

public:
    VAO();
    ~VAO();
    VAO(VAO&& v) noexcept;
    VAO& operator=(VAO v);

    GLuint id() const { return _id; }

    void bind() const;
    static void attrib_pointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
        const void* pointer);

    void enable_attrib(GLuint index);
};

}