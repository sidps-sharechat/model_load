#include <Renderer.h>

void VertexArray::GenerateBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

void VertexArray::BindVAO()
{
    glBindVertexArray(VAO);
}

void VertexArray::UnBindVAO()
{
    glBindVertexArray(0);
}

void VertexArray::BindVBO(int vertexCount, GLsizeiptr strideSize, void *pointer)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * strideSize, pointer, GL_STATIC_DRAW);
}
void VertexArray::BindEBO(int indicesCount, void *pointer)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), pointer, GL_STATIC_DRAW);
}

void VertexArray::UnBindVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArray::UnBindEBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArray::SetAttribArray(int layoutLayer, int count, GLsizeiptr strideSize, const void *pointer)
{
    glEnableVertexAttribArray(layoutLayer);
    glVertexAttribPointer(layoutLayer, count, GL_FLOAT, GL_FALSE, strideSize, pointer);
}

void VertexArray::DrawTriangles(int vertexCount, int startIndex)
{
    BindVAO();
    glDrawArrays(GL_TRIANGLES, startIndex, vertexCount);
    UnBindVAO();
}

void VertexArray::DrawElements(int indicesCount)
{
    BindVAO();
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
    UnBindVAO();
}

void VertexArray::FreeData()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
