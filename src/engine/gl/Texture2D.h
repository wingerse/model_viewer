#pragma once

#include "glad.h"
#include "Texture.h"

namespace engine::gl {

class Texture2D: public Texture {

public:
    explicit Texture2D(const char *path);
    void bind();
    static void param(GLenum name, GLint param);
};

}