#pragma once

#include "glad.h"

namespace engine::gl {

class Texture {
    GLuint _id;
    bool _moved;

public:
    Texture();
    ~Texture();
    Texture(Texture&& p) noexcept;
    Texture& operator=(Texture p);
    GLuint id() const { return _id; }
};

}