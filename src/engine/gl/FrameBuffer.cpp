#include <utility>
#include "FrameBuffer.h"

namespace engine::gl {

RenderBuffer::RenderBuffer(int width, int height)
    : _moved{false}
{
    glGenRenderbuffers(1, &_id);
    glBindRenderbuffer(GL_RENDERBUFFER, _id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

RenderBuffer::~RenderBuffer()
{
    if (!_moved) {
        glDeleteRenderbuffers(1, &_id);
    }
}

RenderBuffer::RenderBuffer(RenderBuffer&& r) noexcept
    : _id{r._id}
    , _moved{r._moved}
{
    r._moved = true;
}

RenderBuffer& RenderBuffer::operator=(RenderBuffer r)
{
    using std::swap;
    swap(_id, r._id);
    swap(_moved, r._moved);
    return *this;
}

FrameBuffer::FrameBuffer(GLuint id, int width, int height)
    : _depth_stencil(width, height)
    , _moved{false}
{
    glGenFramebuffers(1, &_id);
    glBindFramebuffer(GL_FRAMEBUFFER, _id);

    glBindTexture(GL_TEXTURE_2D, _color.id());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _color.id(), 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depth_stencil.id());
}

FrameBuffer::~FrameBuffer()
{
    if (!_moved) {
        glDeleteFramebuffers(1, &_id);
    }
}

FrameBuffer::FrameBuffer(FrameBuffer&& f) noexcept
    : _id{f._id}
    , _color{std::move(f._color)}
    , _depth_stencil(std::move(f._depth_stencil))
    , _moved{f._moved}
{
    f._moved = true;
}

FrameBuffer& FrameBuffer::operator=(FrameBuffer f)
{
    using std::swap;

    swap(_id, f._id);
    swap(_color, f._color);
    swap(_depth_stencil, f._depth_stencil);
    swap(_moved, f._moved);

    return *this;
}

void FrameBuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _id);
}

}