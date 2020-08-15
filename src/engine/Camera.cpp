#include "Camera.h"

using namespace math;

namespace engine {

Camera::Camera(math::mat4 proj_matrix, math::vec3 pos, float yaw, float pitch)
    : _proj_matrix{proj_matrix}
    , _pos{pos}
{
    set_yaw_pitch(yaw, pitch);
    update_view_matrix();
}

void Camera::move_forward(float val)
{
    vec3 forward = vec3{_dir.x(), 0, _dir.z()}.normalized();
    _pos += forward * val;
}

void Camera::move_backward(float val)
{
    move_forward(-val);
}

void Camera::move_right(float val)
{
    vec3 right = (vec3{0, 1, 0} * -_dir).normalized();
    _pos += right * val; 
}

void Camera::move_left(float val)
{
    move_right(-val);
}

void Camera::move_up(float val)
{
    _pos = vec3{_pos.x(), _pos.y()+val, _pos.z()};
}

void Camera::move_down(float val)
{
    move_up(-val);
}

void Camera::set_yaw_pitch(float yaw, float pitch)
{
    if (yaw > 180) yaw -= 180*2;
    if (yaw < -180) yaw += 180*2;
    if (pitch > 89) pitch = 89;
    if (pitch < -89) pitch = -89;

    _yaw = yaw;
    _pitch = pitch;
    yaw = radians(yaw);
    pitch = radians(pitch);

    float hlen = cosf(pitch);
    float x = hlen * -sinf(yaw);
    float y = sinf(pitch);
    float z = hlen * cosf(yaw);

    _dir = vec3{x, y, z}.normalized();
}

void Camera::update_view_matrix()
{
    _view_matrix = look(_pos, _dir, vec3{0, 1, 0});
}

}