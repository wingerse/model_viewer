#pragma once

#include "Texture.h"
#include "VAO.h"
#include "buffers.h"
#include "Program.h"
#include <array>
#include <string>

namespace engine::gl {

class Cubemap {
    Texture _texture;
    VAO _vao;
    VBO _vbo;
    Program _program;

public:
    explicit Cubemap(const std::array<std::string, 6>& faces_paths);
    void draw(const math::mat4& view, const math::mat4& proj) const;
};

}