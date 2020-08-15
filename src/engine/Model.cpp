#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <exception>
#include <algorithm>
#include "gl/Texture2D.h"

using namespace math;

namespace engine {

static mat4 aimat4_to_mat4(const aiMatrix4x4& m)
{
    return {
        m.a1, m.a2, m.a3, m.a4,
        m.b1, m.b2, m.b3, m.b4,
        m.c1, m.c2, m.c3, m.c4,
        m.d1, m.d2, m.d3, m.d4,
    };
}

std::shared_ptr<Material::Texture> Model::load_texture(
    aiMaterial* material,
    std::vector<std::shared_ptr<Material::Texture>>& textures,
    aiTextureType type)
{
    aiString ai_path;
    material->GetTexture(type, 0, &ai_path);
    std::string path{ai_path.C_Str()};
    path = _directory + path;

    auto it = std::find_if(textures.begin(), textures.end(), [&](auto& e) { return e->path == path; });
    if (it == textures.end()) {
        auto ret = std::make_shared<Material::Texture>(Material::Texture{gl::Texture2D{path.c_str()}, std::move(path)});

        gl::Texture2D::param(GL_TEXTURE_WRAP_S, GL_REPEAT);
        gl::Texture2D::param(GL_TEXTURE_WRAP_T, GL_REPEAT);
        gl::Texture2D::param(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        gl::Texture2D::param(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        textures.push_back(ret);

        return ret;
    }

    return *it;
}

std::shared_ptr<Mesh> Model::load_mesh(aiMesh* mesh, std::vector<std::shared_ptr<Material::Texture>>& textures)
{
    std::vector<Mesh::Vertex> vertices{};

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        auto ai_pos = mesh->mVertices[i];
        vec3 pos{ai_pos.x, ai_pos.y, ai_pos.z};

        if (!mesh->HasNormals()) throw std::runtime_error{"no normals"};
        auto ai_normal = mesh->mNormals[i];
        vec3 normal{ai_normal.x, ai_normal.y, ai_normal.z};

        if (!mesh->HasTextureCoords(0)) throw std::runtime_error{"no uvs"};
        auto ai_uv = mesh->mTextureCoords[0][i];
        vec2 uv{ai_uv.x, ai_uv.y};

        vertices.push_back(Mesh::Vertex{pos, normal, uv});
    }

    std::vector<GLuint> indices{};

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    const aiScene* scene = _importer.GetScene();
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    auto diffuse = load_texture(material, textures, aiTextureType_DIFFUSE);
    auto specular = load_texture(material, textures, aiTextureType_SPECULAR);
    float shininess;
    material->Get(AI_MATKEY_SHININESS, shininess);

    Material mat{std::move(diffuse), std::move(specular), shininess};

    return std::make_shared<Mesh>(std::move(vertices), std::move(indices), std::move(mat));
}

std::vector<std::shared_ptr<Mesh>> Model::load_meshes()
{
    std::vector<std::shared_ptr<Mesh>> meshes{};
    std::vector<std::shared_ptr<Material::Texture>> textures;

    const aiScene* scene = _importer.GetScene();
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];
        meshes.push_back(load_mesh(mesh, textures));
    }
    return meshes;
}

void Model::process_node(aiNode* node, std::vector<std::shared_ptr<Mesh>>& meshes, const math::mat4& transform)
{
    mat4 node_transform = aimat4_to_mat4(node->mTransformation)*transform;

    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        _meshes.emplace_back(node_transform, meshes[node->mMeshes[i]]);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        process_node(node->mChildren[i], meshes, node_transform);
    }
}

Model::Model(const std::string& path)
    : _importer{}
    , _meshes()
{
    auto pos = path.find_last_of('/');
    _directory = pos == std::string::npos ? "" : path.substr(0, pos + 1);
    const aiScene* scene = _importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
    if (!scene) {
        throw std::runtime_error{_importer.GetErrorString()};
    }
    auto meshes = load_meshes();
    process_node(_importer.GetScene()->mRootNode, meshes, identity);
}

void Model::draw(gl::Program& program, const mat4& model, const mat4& view, const mat4& proj)
{
    for (auto[first, second] : _meshes) {
        mat4 _model = model*first;
        mat4 modelview = view*_model;
        program.set_uniform("modelview", modelview);
        program.set_uniform("proj", proj);
        mat4 normal_matrix = modelview.inverse().transpose();
        program.set_uniform("normal_matrix", normal_matrix);
        second->draw(program);
    }
}

}