#include <utility>
#include "VAO.h"

namespace engine::gl {

VAO::VAO()
    : _moved{false}
{
    glGenVertexArrays(1, &_id);
}

VAO::~VAO()
{
    if (!_moved) {
        glDeleteVertexArrays(1, &_id);
    }
}

VAO::VAO(VAO&& v) noexcept
    : _id{v._id}
    , _moved{v._moved}
{
    v._moved = true;
}

VAO& VAO::operator=(VAO v)
{
    using std::swap;

    swap(_id, v._id);
    swap(_moved, v._moved);

    return *this;
}

void VAO::bind() const
{
    glBindVertexArray(_id);
}

void VAO::attrib_pointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
    const void* pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VAO::enable_attrib(GLuint index)
{
    glEnableVertexArrayAttrib(_id, index);
}


}