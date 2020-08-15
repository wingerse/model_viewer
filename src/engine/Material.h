#pragma once

#include "gl/Texture2D.h"
#include <string>
#include <memory>

namespace engine {

struct Material {
    struct Texture {
        gl::Texture2D texture;
        std::string path;
    };

    std::shared_ptr<Texture> diffuse;
    std::shared_ptr<Texture> specular;
    float shininess;
};

}