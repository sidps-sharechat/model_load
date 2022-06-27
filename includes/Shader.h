#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get opengl Files
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Camera.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

enum SHADER_COMPONENT
{
	VERTEX_SHADER,
	FRAGMENT_SHADER,
	GEOMETRY_SHADER
};

// Shader Class
class Shader
{
public:
	unsigned int ID;										  // shader program ID
	Shader();												  // Empty Constrcutor
	Shader(const char *vertexPath, const char *fragmentPath); // creates and links shader program
	Shader(const std::string &vertexPath, const std::string &fragmentPath);
	void CreateShader(const char *vertexPath, const char *fragmentPath);
	unsigned int CompileShader(const char *code, SHADER_COMPONENT type);
	// uses shader program
	void use();
	void FreeData();
	// utility functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void SetMatrices(glm::mat4 model, glm::mat4 view, glm::mat4 projection);

private:
	// utility function for checking errors
	void CheckCompileErrors(unsigned int shader, std::string type);
};

#endif // !SHADER_H
