/* 
AUTHOR       : Angel Ortiz (angelo12 AT vt DOT edu)
PROJECT      : Hybrid Rendering Engine 
LICENSE      : This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
DATE	     : 2018-09-08
*/

//Includes
#include "model.h"
#include "geometry.h"
#include "glm/glm.hpp"
#include "fileManager.h"
#include "glad/glad.h"
#include <string>

namespace {
unsigned int createSolidTexture(
    std::unordered_map<std::string, Texture>& textureAtlas,
    const std::string& key,
    unsigned char r,
    unsigned char g,
    unsigned char b,
    unsigned char a)
{
    if (textureAtlas.count(key) != 0) {
        return textureAtlas.at(key).textureID;
    }

    unsigned int textureID = 0;
    unsigned char pixel[4] = {r, g, b, a};
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    Texture texture;
    texture.textureID = textureID;
    texture.width = 1;
    texture.height = 1;
    texture.nComponents = 4;
    texture.path = key;
    textureAtlas.insert({key, texture});
    return textureID;
}

unsigned int loadTextureForTypes(
    const aiMaterial* material,
    const std::string& directory,
    std::unordered_map<std::string, Texture>& textureAtlas,
    std::initializer_list<aiTextureType> textureTypes,
    bool srgb)
{
    aiString texturePath;
    for (aiTextureType type : textureTypes) {
        if (material->GetTextureCount(type) == 0) {
            continue;
        }

        std::string fullTexturePath = directory;
        material->GetTexture(type, 0, &texturePath);
        fullTexturePath.append(texturePath.C_Str());

        if (textureAtlas.count(fullTexturePath) == 0) {
            Texture texture;
            texture.loadTexture(fullTexturePath, srgb);
            textureAtlas.insert({fullTexturePath, texture});
        }

        return textureAtlas.at(fullTexturePath).textureID;
    }

    return 0;
}
}

//We use assimp to load all our mesh files this 
void Model::loadModel(std::string path){
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_OptimizeMeshes |aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
    if (scene == nullptr || scene->mRootNode == nullptr) {
        printf("Assimp failed to load model: %s\n", path.c_str());
        return;
    }

    //useful for texture indexing later
    fileExtension = FLOAD::getFileExtension(path);
    directory = path.substr(0, path.find_last_of('/'));
    directory += "/";

    //begin recursive processing of loaded model
    processNode(scene->mRootNode, scene);
}

//The model currently is just a vessel for the meshes of the scene,
//In a future revision this will probably change
void Model::draw(const Shader &shader, const  bool textured){
    shader.setBool("IBL", IBL);
    for(int i = 0; i < meshes.size(); ++i){
        meshes[i].draw(shader, textured);
    }
}

//Stub, to fill in later
void Model::update(const unsigned int deltaT){
}

//Basic ASSIMP scene tree traversal, taken from the docs
void Model::processNode(aiNode *node, const aiScene *scene){
    //Process all the node meshes
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh,scene));
    }

    //process all the node children recursively
    for(unsigned int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }
}

/*
1. Process vertices 
2. Process indices
3. Process materials

TODO::Refactoring target?
*/
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene){
    std::vector<Vertex> vertices;
    std::vector<unsigned int > indices;
    std::vector<unsigned int > textures;

    //Process vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; ++i){
        //Process vertex positions, normals, tangents, bitangents, and texture coordinates
        Vertex vertex;
        glm::vec3 vector;

        //Process position
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        //Process tangent
        if (mesh->HasTangentsAndBitangents()){
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;

            //Process biTangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.biTangent = vector;
        }
        else{
            vertex.tangent = glm::vec3(1.0f, 0.0f, 0.0f);
            vertex.biTangent = glm::vec3(0.0f, 1.0f, 0.0f);
        }

        //Process normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        //Process texture coords
        if (mesh->HasTextureCoords(0)){
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else{
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    //Process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; ++i){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; ++j){
            indices.push_back(face.mIndices[j]);
        }
    }

    //Process material and texture info
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    textures = processTextures(material);

    return Mesh(vertices, indices, textures);
}

/*
FIXES::
1. Have more than one texture per type
2. Make this it's own material class that takes care of it properly
*/
std::vector<unsigned int> Model::processTextures(const aiMaterial *material){
    std::vector<unsigned int> textures(5, 0);

    // Expected shader slot order:
    // 0 albedo, 1 emissive, 2 normals, 3 AO/lightmap, 4 metallic-roughness
    textures[0] = loadTextureForTypes(
        material,
        directory,
        textureAtlas,
        {aiTextureType_DIFFUSE},
        true);

    textures[1] = loadTextureForTypes(
        material,
        directory,
        textureAtlas,
        {aiTextureType_EMISSIVE},
        true);

    textures[2] = loadTextureForTypes(
        material,
        directory,
        textureAtlas,
        {aiTextureType_NORMALS, aiTextureType_HEIGHT},
        false);

    textures[3] = loadTextureForTypes(
        material,
        directory,
        textureAtlas,
        {aiTextureType_LIGHTMAP, aiTextureType_AMBIENT},
        false);

    textures[4] = loadTextureForTypes(
        material,
        directory,
        textureAtlas,
        {aiTextureType_UNKNOWN, aiTextureType_SPECULAR, aiTextureType_SHININESS},
        false);

    if (textures[0] == 0) {
        textures[0] = createSolidTexture(textureAtlas, "__default_albedo_white__", 255, 255, 255, 255);
    }
    if (textures[1] == 0) {
        textures[1] = createSolidTexture(textureAtlas, "__default_emissive_black__", 0, 0, 0, 255);
    }
    if (textures[4] == 0) {
        textures[4] = createSolidTexture(textureAtlas, "__default_metalrough__", 0, 255, 0, 255);
    }

    return textures;
}
