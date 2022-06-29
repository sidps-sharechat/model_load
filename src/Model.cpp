#include "Model.h"

namespace Shutter
{
    ModelMesh::ModelMesh(std::vector<ModelVertex> _vertices, std::vector<unsigned int> _indices,
                         std::vector<ModelTexture> _textures)
    {
        vertices = _vertices;
        indices = _indices;
        textures = _textures;
        SetupVertexArray();
        //        SetupVertexBuffer(shader);
    }

    void ModelMesh::Draw()
    {
        // TODO: Use Shader
        // TODO: Draw given mesh using Shader
        unsigned int diffusedNR = 1;
        unsigned int specularNR = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            // TODO: Set Active Texture
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
            {
                number = std::to_string(diffusedNR++);
            }
            else if (name == "texture_specular")
            {
                number = std::to_string(specularNR++);
            }
            // TODO: Set Texture to current i
        }
        // TODO: Unbind Texture

        // TODO: Draw Vertex Array
    }

    void ModelMesh::Draw(Shader &shdr)
    {
        // TODO: Use Shader
        shdr.use();
        // TODO: Draw given mesh using Shader
        unsigned int diffusedNR = 1;
        unsigned int specularNR = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            // TODO: Set Active Texture
            set_active_texture(i);
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
            {
                number = std::to_string(diffusedNR++);
            }
            else if (name == "texture_specular")
            {
                number = std::to_string(specularNR++);
            }
            // TODO: Set Texture to current i
            shdr.setFloat(("material." + name + number), i);
            bind_texture(textures[i].id);
        }
        // TODO: Unbind Texture
        unbind_texture();

        // TODO: Draw Vertex Array
        vArray.DrawElements(indices.size());
    }

    void ModelMesh::FreeData() // TODO
    {
        vArray.FreeData();
    }

    void ModelMesh::SetupVertexArray()
    {
        vArray.GenerateBuffers();
        vArray.BindVAO();
        vArray.BindVBO(vertices.size(), sizeof(ModelVertex), &vertices[0]);
        vArray.BindEBO(indices.size(), &indices[0]);
        vArray.SetAttribArray(0, 3, sizeof(ModelVertex));
        vArray.SetAttribArray(1, 3, sizeof(ModelVertex), (void *)offsetof(ModelVertex, normal));
        vArray.SetAttribArray(2, 2, sizeof(ModelVertex), (void *)offsetof(ModelVertex, texUV));
        vArray.UnBindVBO();
        vArray.UnBindVAO();
    }

    // void ModelMesh::SetupVertexBuffer(Ref<Shader> &shader)
    // {
    //            GLCall(glBindVertexArray(m_VertexArrayRendererID));
    //            m_VertexBuffer = VertexBuffer::Create(vertices.data(),(uint32_t)(vertices.size()* sizeof(ModelVertex)));
    //            m_IndexBuffer=IndexBuffer::Create(indices.data(),(uint32_t)(indices.size()*sizeof(unsigned int)));
    //     //    spec.Shader=shader;
    //            spec.DebugName="Model Mesh";
    //            spec.Layout={{ShaderDataType::Float3,"a_Position"},
    //                                  {ShaderDataType::Float3,"a_Normal"},
    //                                  {ShaderDataType::Float2,"a_TexCoord"}};
    //            for (int i=0;i<spec.Layout.GetElementCount();i++)
    //            {
    //                auto element=spec.Layout.GetElements()[i];
    //                GLCall(glEnableVertexAttribArray(i));
    //                GLCall(glVertexAttribPointer(i,
    //                                             element.GetComponentCount(),
    //                                             GL_FLOAT,
    //                                             element.Normalized ? GL_TRUE : GL_FALSE,
    //                                             spec.Layout.GetStride(),
    //                                             (const void *) (intptr_t) element.Offset));
    //            }
    //            GLCall(glBindVertexArray(0));
    // }

    Model::Model(std::string path)
    {
        LoadModel(path);
    }

    void Model::Draw() // TODO: Call using Shader
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            meshes[i].Draw();
        }
    }

    void Model::Draw(Shader &shdr)
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            meshes[i].Draw(shdr);
        }
    }

    void Model::FreeData()
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            meshes[i].FreeData();
        }
    }

    void Model::PrintData()
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            ModelMesh mesh = meshes[i];
            for (unsigned int j = 0; j < mesh.vertices.size(); j++)
            {
                ModelVertex vertex = mesh.vertices[j];
                std::cout << "Vertex: " << j << std::endl;
                std::cout << "Position: " << vertex.position.x << " " << vertex.position.y << " " << vertex.position.z << std::endl;
                std::cout << "Normal: " << vertex.normal.x << " " << vertex.normal.y << " " << vertex.normal.z << std::endl;
                std::cout << "UV: " << vertex.texUV.x << " " << vertex.texUV.y << std::endl;
            }
        }
    }

    void Model::LoadModel(std::string path)
    {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));
        ProcessNode(scene->mRootNode, scene);
    }

    void Model::ProcessNode(aiNode *node, const aiScene *scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(ProcessMesh(mesh, scene));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    ModelMesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
    {
        std::vector<ModelVertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<ModelTexture> textures;

        // Vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            ModelVertex vertex;

            // Position
            glm::vec3 pos;
            pos.x = mesh->mVertices[i].x;
            pos.y = mesh->mVertices[i].y;
            pos.z = mesh->mVertices[i].z;
            vertex.position = pos;

            // Normal
            glm::vec3 norm(0.0f);
            if (mesh->HasNormals())
            {
                norm.x = mesh->mNormals[i].x;
                norm.y = mesh->mNormals[i].y;
                norm.z = mesh->mNormals[i].z;
            }
            vertex.normal = norm;

            // Texture
            glm::vec2 tex(0.0f);
            if (mesh->mTextureCoords[0])
            {
                tex.x = mesh->mTextureCoords[0][i].x;
                tex.y = mesh->mTextureCoords[0][i].y;
            }
            vertex.texUV = tex;

            vertices.push_back(vertex);
        }

        // Indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        // Textures
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

            // Diffuse
            std::vector<ModelTexture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            // Specular
            std::vector<ModelTexture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return ModelMesh(vertices, indices, textures);
    }

    std::vector<ModelTexture> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
    {
        std::vector<ModelTexture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            bool skip = false;
            for (unsigned int j = 0; j < texturesLoaded.size(); j++)
            {
                if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(texturesLoaded[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip)
            {
                ModelTexture tex;
                std::string fileName = directory + '/' + std::string(str.C_Str());
                // TODO: Implement for Shutter
                tex.id = load_texture_from_path(fileName);
                tex.type = typeName;
                tex.path = std::string(str.C_Str());
                textures.push_back(tex);
                texturesLoaded.push_back(tex);
            }
        }
        return textures;
    }
}