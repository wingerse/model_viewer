#pragma once

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Mesh.h"
#include <vector>
#include <utility>

namespace engine {

class Model {
    Assimp::Importer _importer;
    std::string _directory;
    std::vector<std::pair<math::mat4, std::shared_ptr<Mesh>>> _meshes;

    std::shared_ptr<Material::Texture> load_texture(
        aiMaterial* material, 
        std::vector<std::shared_ptr<Material::Texture>> &textures, 
        aiTextureType type);

    std::shared_ptr<Mesh> load_mesh(aiMesh* mesh, std::vector<std::shared_ptr<Material::Texture>> &textures);
    std::vector<std::shared_ptr<Mesh>> load_meshes();

    void process_node(aiNode* node, std::vector<std::shared_ptr<Mesh>>& meshes, const math::mat4& transform);
public:
    explicit Model(const std::string& path);
    void draw(gl::Program& program, const math::mat4& model, const math::mat4& view, const math::mat4& proj);
};

}