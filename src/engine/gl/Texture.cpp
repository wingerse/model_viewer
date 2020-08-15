#include "Texture.h"
#include <utility>

namespace engine::gl {

Texture::Texture()
    : _moved{false}
{
    glGenTextures(1, &_id);
}

Texture::~Texture()
{
    if (_moved) return;
    glDeleteTextures(1, &_id);
}

Texture::Texture(Texture&& p) noexcept
    : _id{p._id}
    , _moved{p._moved}
{
    p._moved = true;
}

Texture& Texture::operator=(Texture p)
{
    using std::swap;

    swap(_id, p._id);
    swap(_moved, p._moved);

    return *this;
}

}