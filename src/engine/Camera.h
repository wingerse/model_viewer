#pragma once

#include "../math/math.h"

namespace engine {

class Camera {
    math::mat4 _proj_matrix;
    math::mat4 _view_matrix;
    math::vec3 _pos;
    math::vec3 _dir;
    float _yaw;
    float _pitch;

public:
    Camera(math::mat4 proj_matrix, math::vec3 pos, float yaw, float pitch);
    math::mat4 view_matrix() { return _view_matrix; }
    math::mat4 proj_matrix() { return _proj_matrix; }
    math::vec3 pos() { return _pos; }
    void set_yaw_pitch(float yaw, float pitch);
    void set_proj_matrix(math::mat4 proj_matrix) { _proj_matrix = proj_matrix; }
    float yaw() { return _yaw; }
    float pitch() { return _pitch; }
    void move_forward(float val);
    void move_backward(float val);
    void move_right(float val);
    void move_left(float val);
    void move_up(float val);
    void move_down(float val);
    void update_view_matrix();
};

}
