#include "Cubemap.h"
#include "../stb_image.h"

using namespace math;

namespace engine::gl {

std::array vertices = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

const char *vertex_src = R"glsl(
#version 460 core
layout (location = 0) in vec3 pos;

out vec3 _tex_coords;

uniform mat4 view;
uniform mat4 proj;

void main()
{
    _tex_coords = pos;
    gl_Position = (proj * view * vec4(pos, 1.0)).xyww;
}
)glsl";

const char *fragment_src = R"glsl(
#version 460 core
out vec4 color;

in vec3 _tex_coords;

uniform samplerCube skybox;

void main()
{
    color = texture(skybox, _tex_coords);
}
)glsl";

Cubemap::Cubemap(const std::array<std::string, 6>& faces_paths)
    : _program(vertex_src, fragment_src)
{
    _vao.bind();
    _vbo.bind();
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture.id());

    for (size_t i = 0; i < faces_paths.size(); i++) {
        int x, y, channels;
        stbi_set_flip_vertically_on_load(false);
        unsigned char *data = stbi_load(faces_paths[i].c_str(), &x, &y, &channels, STBI_rgb);
        stbi_set_flip_vertically_on_load(true);
        if (!data) {
            throw std::runtime_error{stbi_failure_reason()};
        }
        glTexImage2D(static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i), 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    VBO::data(vertices.size()*sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    VAO::attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    _vao.enable_attrib(0);
}

void Cubemap::draw(const mat4& view, const mat4& proj) const
{
    _program.use();
    _vao.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture.id());
    _program.set_uniform("skybox", 0);
    _program.set_uniform("view", remove_translation(view));
    _program.set_uniform("proj", proj);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

}
