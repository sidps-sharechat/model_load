#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

// glm libraries for math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Camera.h>
#include <Texture.h>

class VertexArray
{
public:
    unsigned int VAO, VBO, EBO;
    void GenerateBuffers();
    void BindVAO();
    void UnBindVAO();
    void UnBindVBO();
    void UnBindEBO();
    void BindVBO(int vertexCount, GLsizeiptr strideSize, void *pointer);
    void BindEBO(int indicesCount, void *pointer);
    void SetAttribArray(int layoutLayer, int count, GLsizeiptr strideSize, const void *pointer = (void *)0);
    void DrawTriangles(int vertexCount, int startIndex);
    void DrawElements(int indicesCount);
    void FreeData();

private:
};

#endif