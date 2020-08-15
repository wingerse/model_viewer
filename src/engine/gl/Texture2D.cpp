#include "Texture2D.h"
#include <cstddef>
#include "../stb_image.h"
#include <stdexcept>

namespace engine::gl {

Texture2D::Texture2D(const char *path)
{
    bind();

    int x, y, channels;
    unsigned char *data = stbi_load(path, &x, &y, &channels, STBI_rgb_alpha);
    if (!data) {
        throw std::runtime_error{stbi_failure_reason()};
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, id());
}

void Texture2D::param(GLenum name, GLint param)
{
    glTexParameteri(GL_TEXTURE_2D, name, param);
}

}