#ifndef TEXTURE_H
#define TEXTURE_H

// Header declarations
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <FileSystem.h>

// Standard Headers
#include <iostream>

// Types of Textures
enum TEXTURE_TYPE
{
    TEXTURE_DIFFUSE,
    TEXTURE_SPECULAR,
    TEXTURE_EMMISION,
    TEXTURE_NORMAL,
    TEXTURE_HEIGHT,
};

// Texture typestrings
extern std::string textureTypeStrings[5];

// Texture Struct
struct Texture
{
    unsigned int id;  // The ID of the loaded texture
    std::string type; // The type of texture loaded
    std::string path; // Path to the texture file
    // Texture Struct Empty Constructor
    Texture() {}
    // Texture Struct Constructor
    Texture(unsigned int id_, std::string type_, std::string path_) : id(id_), type(type_), path(path_) {}
};

// Texture Loading

// Loads a Texture and returns id
unsigned int load_texture_from_path(const char *path, bool isDiffuse = true, bool toClamp = false);
// Loads a Texture and returns id
unsigned int load_texture_from_path(const std::string &path, bool isDiffuse = true, bool toClamp = false);

// Generating Textures

// Generates a Texture and returns its id
unsigned int generate_texture();
// Binds a Texture to current memory
void bind_texture(unsigned int id);
// UnBinds the currently bound texture
void unbind_texture();
// Sets Active texture via id
void set_active_texture(int index);

#endif // !TEXTURE_H
