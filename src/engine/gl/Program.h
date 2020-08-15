#pragma once

#include "glad.h"
#include "../../math/math.h"

namespace engine::gl {

class Program {
    GLuint _id;

public:
    Program(const char *vertex_src, const char *fragment_src);
    ~Program();
    Program(Program&& p) noexcept ;
    Program& operator=(Program p);
    GLuint id() const { return _id; }
    void use() const;
    GLint get_uniform_location(const char *name) const;
    void set_uniform(const char *name, math::vec4 vec) const;
    void set_uniform(const char *name, math::vec3 vec) const;
    void set_uniform(const char *name, const math::mat4& mat) const;
    void set_uniform(const char *name, GLint i) const;
    void set_uniform(const char *name, GLfloat f) const;
};

}