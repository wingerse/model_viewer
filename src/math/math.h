#pragma once

#include <cmath>

namespace math {

class vec2;
class vec3;
class vec4;
class mat4;

class vec2 {
    float _x;
    float _y;

public:
    constexpr vec2(): _x{}, _y{} {}

    constexpr vec2(float x, float y): _x{x}, _y{y} {}
    constexpr explicit vec2(const vec3& v);

    constexpr float x() const { return _x; }
    constexpr float y() const { return _y; }

    constexpr bool operator==(vec2 o) const 
    {
        return _x == o._x && _y == o._y;
    }

    constexpr bool operator!=(vec2 o) const 
    {
        return !(*this == o);
    }

    constexpr vec2 operator+(vec2 o) const
    {
        return { _x + o._x, _y + o._y };
    }

    constexpr vec2 operator+=(vec2 o)
    {
        return *this = *this + o;
    }

    constexpr vec2 operator*(float val) const
    {
        return { _x * val, _y * val };
    }

    constexpr vec2 operator*=(float val) 
    {
        return *this = *this * val;
    }

    constexpr vec2 operator-() const 
    {
        return *this * -1;
    }

    constexpr vec2 operator-(vec2 o) const
    {
        return *this + -o;
    }

    constexpr vec2 operator-=(vec2 o)
    {
        return *this = *this - o;
    }

    constexpr float dot(vec2 o) const
    {
        return _x * o._x + _y * o._y;
    }

    constexpr float len_sqr() const
    {
        return _x * _x + _y * _y;
    }

    float len() const
    {
        return sqrtf(len_sqr());
    }

    vec2 normalized() const
    {
        return *this * (1 / len());
    }
};

class vec3 {
    float _x;
    float _y;
    float _z;

public:
    constexpr vec3() : _x{}, _y{}, _z{} {}

    constexpr vec3(float x, float y, float z)
        : _x { x }
        , _y { y }
        , _z { z }
    {
    }

    constexpr vec3(vec2 v, float z): _x{v.x()}, _y{v.y()}, _z{z} {}
    constexpr explicit vec3(const vec4& v);

    constexpr float x() const { return _x; }
    constexpr float y() const { return _y; }
    constexpr float z() const { return _z; }

    constexpr bool operator==(vec3 o) const 
    {
        return _x == o._x && _y == o._y && _z == o._z;
    }

    constexpr bool operator!=(vec3 o) const 
    {
        return !(*this == o);
    }

    constexpr vec3 operator+(vec3 o) const
    {
        return { _x + o._x, _y + o._y, _z + o._z };
    }

    constexpr vec3 operator+=(vec3 o)
    {
        return *this = *this + o;
    }

    constexpr vec3 operator*(float val) const
    {
        return { _x * val, _y * val, _z * val };
    }

    constexpr vec3 operator*=(float val) 
    {
        return *this = *this * val;
    }

    constexpr vec3 operator-() const 
    {
        return *this * -1;
    }

    constexpr vec3 operator-(vec3 o) const
    {
        return *this + -o;
    }

    constexpr vec3 operator-=(vec3 o)
    {
        return *this = *this - o;
    }

    constexpr vec3 operator*(vec3 o) const
    {
        return {
            _y * o._z - _z * o._y,
            _z * o._x - _x * o._z,
            _x * o._y - _y * o._x,
        };
    }

    constexpr vec3 operator*=(vec3 o) 
    {
        return *this = *this * o;
    }

    constexpr float dot(vec3 o) const
    {
        return _x * o._x + _y * o._y + _z * o._z;
    }

    constexpr float len_sqr() const
    {
        return _x * _x + _y * _y + _z * _z;
    }

    float len() const
    {
        return sqrtf(len_sqr());
    }

    vec3 normalized() const
    {
        return *this * (1 / len());
    }
};

constexpr vec2::vec2(const vec3& v): _x{v.x()}, _y{v.y()} {}

class vec4 {
    float _x;
    float _y;
    float _z;
    float _w;

public:
    constexpr vec4(): _x{}, _y{}, _z{}, _w{} {}

    constexpr vec4(float x, float y, float z, float w)
        : _x { x }
        , _y { y }
        , _z { z }
        , _w { w }
    {
    }

    constexpr vec4(vec3 v, float w) 
        : _x{v.x()}
        , _y{v.y()}
        , _z{v.z()}
        , _w{w}
    {
    }

    constexpr float x() const { return _x; }
    constexpr float y() const { return _y; }
    constexpr float z() const { return _z; }
    constexpr float w() const { return _w; }

    constexpr bool operator==(vec4 o) const 
    {
        return _x == o._x && _y == o._y && _z == o._z && _w == o._w;
    }

    constexpr bool operator!=(vec4 o) const 
    {
        return !(*this == o);
    }

    constexpr float dot(vec4 o) const
    {
        return _x * o._x + _y * o._y + _z * o._z + _w * o._w;
    }
};

constexpr vec3::vec3(const vec4& v): _x{v.x()}, _y{v.y()}, _z{v.z()} {}

class mat4 {
    float _arr[4][4];

public:
    constexpr mat4(): _arr{} {};

    constexpr mat4(
        float xx, float xy, float xz, float xw,
        float yx, float yy, float yz, float yw,
        float zx, float zy, float zz, float zw,
        float wx, float wy, float wz, float ww
    ) 
        : _arr {
            {xx, xy, xz, xw},
            {yx, yy, yz, yw},
            {zx, zy, zz, zw},
            {wx, wy, wz, ww},
        }
    {
    }

    constexpr const float* operator[](int i) const { return &_arr[i][0]; }

    constexpr bool operator==(const mat4 &o) const 
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (_arr[i][j] != o._arr[i][j]) return false;
            }
        }

        return true;
    }

    constexpr bool operator!=(const mat4& o) const 
    {
        return !(*this == o);
    }

    constexpr mat4 operator+(const mat4 &o) const
    {
        mat4 res;

        for (int i = 0; i < 4; i++) {
            res._arr[i][0] = (*this)[i][0] + o[i][0];
            res._arr[i][1] = (*this)[i][1] + o[i][1];
            res._arr[i][2] = (*this)[i][2] + o[i][2];
            res._arr[i][3] = (*this)[i][3] + o[i][3];
        }

        return res;
    }

    constexpr mat4 operator+=(const mat4 &o)
    {
        return *this = *this + o;
    }

    constexpr mat4 operator*(float val) const
    {
        mat4 res;

        for (int i = 0; i < 4; i++) {
            res._arr[i][0] = (*this)[i][0] * val;
            res._arr[i][1] = (*this)[i][1] * val;
            res._arr[i][2] = (*this)[i][2] * val;
            res._arr[i][3] = (*this)[i][3] * val;
        }

        return res;
    }

    constexpr mat4 operator*=(float val)
    {
        return *this = *this * val;
    }

    constexpr mat4 operator-() const
    {
        return *this * -1;
    }

    constexpr mat4 operator-(const mat4 &o) const
    {
        return *this + -o;
    }

    constexpr mat4 operator-=(const mat4 &o) 
    {
        return *this = *this - o;
    }

    constexpr mat4 operator*(const mat4 &o) const
    {
        mat4 res;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                vec4 a {(*this)[i][0],(*this)[i][1],(*this)[i][2],(*this)[i][3]};
                vec4 b {o[0][j],o[1][j],o[2][j],o[3][j]};
                res._arr[i][j] = a.dot(b);
            }
        } 
    
        return res;
    }

    constexpr vec4 operator*(const vec4 v) const
    {
        float arr[4] {};

        for (int i = 0; i < 4; i++) {
            vec4 a {(*this)[i][0],(*this)[i][1],(*this)[i][2],(*this)[i][3]};
            arr[i] = a.dot(v);
        } 
    
        return {arr[0], arr[1], arr[2], arr[3]};
    }

    constexpr mat4 operator*=(const mat4 &o)
    {
        return *this = *this * o;
    }

    constexpr mat4 transpose() const
    {
        return {
            (*this)[0][0], (*this)[1][0], (*this)[2][0], (*this)[3][0],
            (*this)[0][1], (*this)[1][1], (*this)[2][1], (*this)[3][1],
            (*this)[0][2], (*this)[1][2], (*this)[2][2], (*this)[3][2],
            (*this)[0][3], (*this)[1][3], (*this)[2][3], (*this)[3][3],
        };
    }

    constexpr mat4 inverse() const 
    {
        const mat4& m = *this;

        float S_00 = m[1][1]*(m[2][2]*m[3][3] - m[2][3]*m[3][2]) + 
                    m[1][2]*(m[2][3]*m[3][1] - m[2][1]*m[3][3]) + 
                    m[1][3]*(m[2][1]*m[3][2] - m[2][2]*m[3][1]);
        float S_01 = m[1][0]*(m[2][3]*m[3][2] - m[2][2]*m[3][3]) + 
                    m[1][2]*(m[2][0]*m[3][3] - m[2][3]*m[3][0]) + 
                    m[1][3]*(m[2][2]*m[3][0] - m[2][0]*m[3][2]);
        float S_02 = m[1][0]*(m[2][1]*m[3][3] - m[2][3]*m[3][1]) + 
                    m[1][1]*(m[2][3]*m[3][0] - m[2][0]*m[3][3]) + 
                    m[1][3]*(m[2][0]*m[3][1] - m[2][1]*m[3][0]);
        float S_03 = m[1][0]*(m[2][2]*m[3][1] - m[2][1]*m[3][2]) + 
                    m[1][1]*(m[2][0]*m[3][2] - m[2][2]*m[3][0]) + 
                    m[1][2]*(m[2][1]*m[3][0] - m[2][0]*m[3][1]);
        float S_10 = m[0][1]*(m[2][3]*m[3][2] - m[2][2]*m[3][3]) + 
                    m[0][2]*(m[2][1]*m[3][3] - m[2][3]*m[3][1]) + 
                    m[0][3]*(m[2][2]*m[3][1] - m[2][1]*m[3][2]);
        float S_11 = m[0][0]*(m[2][2]*m[3][3] - m[2][3]*m[3][2]) + 
                    m[0][2]*(m[2][3]*m[3][0] - m[2][0]*m[3][3]) + 
                    m[0][3]*(m[2][0]*m[3][2] - m[2][2]*m[3][0]);
        float S_12 = m[0][0]*(m[2][3]*m[3][1] - m[2][1]*m[3][3]) + 
                    m[0][1]*(m[2][0]*m[3][3] - m[2][3]*m[3][0]) + 
                    m[0][3]*(m[2][1]*m[3][0] - m[2][0]*m[3][1]);
        float S_13 = m[0][0]*(m[2][1]*m[3][2] - m[2][2]*m[3][1]) + 
                    m[0][1]*(m[2][2]*m[3][0] - m[2][0]*m[3][2]) + 
                    m[0][2]*(m[2][0]*m[3][1] - m[2][1]*m[3][0]);
        float S_20 = m[0][1]*(m[1][2]*m[3][3] - m[1][3]*m[3][2]) + 
                    m[0][2]*(m[1][3]*m[3][1] - m[1][1]*m[3][3]) + 
                    m[0][3]*(m[1][1]*m[3][2] - m[1][2]*m[3][1]);
        float S_21 = m[0][0]*(m[1][3]*m[3][2] - m[1][2]*m[3][3]) + 
                    m[0][2]*(m[1][0]*m[3][3] - m[1][3]*m[3][0]) + 
                    m[0][3]*(m[1][2]*m[3][0] - m[1][0]*m[3][2]);
        float S_22 = m[0][0]*(m[1][1]*m[3][3] - m[1][3]*m[3][1]) + 
                    m[0][1]*(m[1][3]*m[3][0] - m[1][0]*m[3][3]) + 
                    m[0][3]*(m[1][0]*m[3][1] - m[1][1]*m[3][0]);
        float S_23 = m[0][0]*(m[1][2]*m[3][1] - m[1][1]*m[3][2]) + 
                    m[0][1]*(m[1][0]*m[3][2] - m[1][2]*m[3][0]) + 
                    m[0][2]*(m[1][1]*m[3][0] - m[1][0]*m[3][1]);
        float S_30 = m[0][1]*(m[1][3]*m[2][2] - m[1][2]*m[2][3]) + 
                    m[0][2]*(m[1][1]*m[2][3] - m[1][3]*m[2][1]) + 
                    m[0][3]*(m[1][2]*m[2][1] - m[1][1]*m[2][2]);
        float S_31 = m[0][0]*(m[1][2]*m[2][3] - m[1][3]*m[2][2]) + 
                    m[0][2]*(m[1][3]*m[2][0] - m[1][0]*m[2][3]) + 
                    m[0][3]*(m[1][0]*m[2][2] - m[1][2]*m[2][0]);
        float S_32 = m[0][0]*(m[1][3]*m[2][1] - m[1][1]*m[2][3]) + 
                    m[0][1]*(m[1][0]*m[2][3] - m[1][3]*m[2][0]) + 
                    m[0][3]*(m[1][1]*m[2][0] - m[1][0]*m[2][1]);
        float S_33 = m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1]) + 
                    m[0][1]*(m[1][2]*m[2][0] - m[1][0]*m[2][2]) + 
                    m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);

        float det = 1/(m[0][0]*S_00 + m[0][1]*S_01 + m[0][2]*S_02 + m[0][3]*S_03);

        return {
            det*S_00, det*S_10, det*S_20, det*S_30, 
            det*S_01, det*S_11, det*S_21, det*S_31, 
            det*S_02, det*S_12, det*S_22, det*S_32, 
            det*S_03, det*S_13, det*S_23, det*S_33, 
        };
    }
};

constexpr mat4 identity = mat4(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
);

constexpr mat4 translate(vec3 v) 
{
    return mat4{
        1, 0, 0, v.x(),
        0, 1, 0, v.y(),
        0, 0, 1, v.z(),
        0, 0, 0, 1,
    };
}

constexpr mat4 remove_translation(const mat4& m)
{
    return {
        m[0][0], m[0][1], m[0][2], 0,
        m[1][0], m[1][1], m[1][2], 0,
        m[2][0], m[2][1], m[2][2], 0,
        m[3][0], m[3][1], m[3][2], 1,
    };
}

constexpr mat4 scale(vec3 v) 
{
    return mat4{
        v.x(), 0,     0,     0,
        0,     v.y(), 0,     0,
        0,     0,     v.z(), 0,
        0,     0,     0,     1,
    };
}

inline mat4 rotate_x(float angle)
{
    float s = sinf(angle), c = cosf(angle);
    return mat4{
        1, 0, 0, 0,
        0, c, -s, 0,
        0, s, c, 0,
        0, 0, 0, 1
    };
}

inline mat4 rotate_y(float angle)
{
    float s = sinf(angle), c = cosf(angle);
    return mat4{
        c, 0, s, 0,
        0, 1, 0, 0,
        -s, 0, c, 0,
        0, 0, 0, 1,
    };
}

inline mat4 rotate_z(float angle)
{
    float s = sinf(angle), c = cosf(angle);
    return mat4{
        c, -s, 0, 0,
        s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

inline mat4 perspective(float fovy, float aspect, float n, float f)
{
    float ntot = 1/tanf(fovy/2);
    return {
        ntot/aspect, 0, 0, 0,
        0, ntot, 0, 0,
        0, 0, (f+n)/(n-f), (2*f*n)/(n-f),
        0, 0, -1, 0,
    };
}

constexpr mat4 ortho(float l, float r, float b, float t, float n, float f)
{
    return {
        2/(r-l), 0, 0, (r+l)/(l-r),
        0, 2/(t-b), 0, (t+b)/(b-t),
        0, 0, 2/(n-f), (f+n)/(n-f),
        0, 0, 0, 1,
    };
}

inline mat4 look(vec3 pos, vec3 dir, vec3 up)
{
    vec3 z = -dir;
    vec3 x = (up * z).normalized();
    vec3 y = z * x;
    mat4 transform = {
        x.x(), x.y(), x.z(), 0,
        y.x(), y.y(), y.z(), 0,
        z.x(), z.y(), z.z(), 0,
        0,     0,     0,     1,
    };
    return transform * translate(-pos);
}

inline mat4 look_at(vec3 pos, vec3 target, vec3 up)
{
    return look(pos, (target-pos).normalized(), up);
}

constexpr float radians(float deg) 
{
    return static_cast<float>(deg * M_PI / 180.0);
}

constexpr float degrees(float rad) 
{
    return static_cast<float>(rad * 180.0 / M_PI);
}

} 