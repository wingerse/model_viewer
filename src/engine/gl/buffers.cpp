#include <utility>
#include "buffers.h"

namespace engine::gl {

Buffer::Buffer()
    : _moved{false}
{
    glGenBuffers(1, &_id);
}

Buffer::~Buffer()
{
    if (!_moved) {
        glDeleteBuffers(1, &_id);
    }
}

Buffer::Buffer(Buffer&& b) noexcept
    : _id{b._id}
    , _moved{false}
{
    b._moved = true;
}

Buffer& Buffer::operator=(Buffer b)
{
    using std::swap;

    swap(_id, b._id);
    swap(_moved, b._moved);

    return *this;
}

void VBO::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id());
}

void VBO::data(GLsizeiptr size, const void* data, GLenum usage)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void EBO::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id());
}

void EBO::data(GLsizeiptr size, const void* data, GLenum usage)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

}