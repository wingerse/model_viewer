#pragma once

#include "glad.h"
#include "Texture.h"

namespace engine::gl {

class RenderBuffer {
    GLuint  _id;
    bool _moved;
public:
    RenderBuffer(int width, int height);
    ~RenderBuffer();
    RenderBuffer(RenderBuffer&& r) noexcept;
    RenderBuffer& operator=(RenderBuffer r);
    GLuint id() const { return _id; }
};

class FrameBuffer {
private:
    GLuint _id;
    Texture _color;
    RenderBuffer _depth_stencil;
    bool _moved;

public:
    FrameBuffer(GLuint id, int width, int height);
    ~FrameBuffer();
    FrameBuffer(FrameBuffer&& f) noexcept;
    FrameBuffer& operator=(FrameBuffer f);
    void bind() const;
};

}