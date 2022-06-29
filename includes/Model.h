#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// TODO: Replace with Shutter headers
#include "Texture.h"
#include "Renderer.h"
#include "Shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// #include <graphics/core/renderer/Mesh.h>
// #include <graphics/core/renderer/Pipeline.h>
// #include "graphics/opengl/include/gl_headers.h"
// //#include <GLES3/gl3.h>
// #include "graphics/opengl/include/OpenGLShader.h"

#include <iostream>
#include <vector>

namespace Shutter
{
    // TODO: Replace Vertex with default
    struct ModelVertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texUV;
    };

    // TODO: Replace Texture with default
    struct ModelTexture
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

    // TODO: Replace Mesh with default
    class ModelMesh
    {
    public:
        std::vector<ModelVertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<ModelTexture> textures;

        ModelMesh(std::vector<ModelVertex> _vertices, std::vector<unsigned int> _indices, std::vector<ModelTexture> _textures);
        void Draw(); // TODO
        void Draw(Shader &shdr);
        void FreeData(); // TODO

    private:
        // RendererID m_VertexArrayRendererID = 0;
        // Ref<VertexBuffer> m_VertexBuffer;
        // Ref<IndexBuffer> m_IndexBuffer;
        // PipelineSpecification spec;

        VertexArray vArray;
        void SetupVertexArray();
        // void SetupVertexBuffer(Ref<Shader> &shader);
    };

    class Model
    {
    public:
        Model(std::string path);
        void Draw(); // TODO: Call using Shader
        void Draw(Shader &shdr);
        void FreeData();
        void PrintData();

    private:
        std::vector<ModelMesh> meshes;
        std::vector<ModelTexture> texturesLoaded;
        std::string directory;

        void LoadModel(std::string path);
        void ProcessNode(aiNode *node, const aiScene *scene);
        ModelMesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
        // TODO: Generate Texture
        std::vector<ModelTexture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    };

}
#endif // MODEL_H