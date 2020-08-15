#include "Mesh.h"
#include <sstream>

namespace engine {

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Material material)
    : _indices_size{(GLsizei)indices.size()}
    , _material{std::move(material)}
{
    _vao.bind();

    _vbo.bind();
    gl::VBO::data(vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    _ebo.bind();
    gl::EBO::data(indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    gl::VAO::attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, pos)));
    _vao.enable_attrib(0);
    gl::VAO::attrib_pointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
    _vao.enable_attrib(1);
    gl::VAO::attrib_pointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv)));
    _vao.enable_attrib(2);
}

void Mesh::draw(gl::Program& program)
{
    glActiveTexture(GL_TEXTURE0);
    program.set_uniform("material.diffuse", 0);
    glBindTexture(GL_TEXTURE_2D, _material.diffuse->texture.id());

    glActiveTexture(GL_TEXTURE1);
    program.set_uniform("material.specular", 1);
    glBindTexture(GL_TEXTURE_2D, _material.specular->texture.id());
    program.set_uniform("material.shininess", _material.shininess);

    _vao.bind();
    glDrawElements(GL_TRIANGLES, _indices_size, GL_UNSIGNED_INT, 0);
}

}