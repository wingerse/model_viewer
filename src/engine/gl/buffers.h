#pragma once

#include "glad.h"

namespace engine::gl {

class Buffer {
    GLuint _id;
    bool _moved;
public:
    Buffer();
    ~Buffer();
    Buffer(Buffer&& b) noexcept;
    Buffer& operator=(Buffer b);

    GLuint id() const { return _id; }
};

class VBO : public Buffer {
public:
    void bind() const;
    static void data(GLsizeiptr size, const void* data, GLenum usage);
};

class EBO : public Buffer {
public:
    void bind() const;
    static void data(GLsizeiptr size, const void* data, GLenum usage);
};

}