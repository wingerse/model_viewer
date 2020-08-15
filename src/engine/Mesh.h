#pragma once

#include "../math/math.h"
#include "gl/glad.h"
#include "gl/Texture2D.h"
#include "gl/Program.h"
#include "Material.h"
#include <vector>
#include <string>
#include <memory>
#include "gl/VAO.h"
#include "gl/buffers.h"

namespace engine {

class Mesh {
public:
    struct Vertex {
        math::vec3 pos;
        math::vec3 normal;
        math::vec2 uv;
    };

private:
    gl::VAO _vao;
    gl::VBO _vbo;
    gl::EBO _ebo;
    GLsizei _indices_size;
    Material _material;

public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Material material);
    void draw(gl::Program& program);
};

}